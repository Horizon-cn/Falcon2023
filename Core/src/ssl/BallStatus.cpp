#include "BallStatus.h"
#include <RobotSensor.h>
#include "BestPlayer.h"
#include "defenceNew/DefenceInfoNew.h"
#include "KickDirection.h"
#include "Global.h"
#include "utils.h"
#include "NormalPlayUtils.h"
#include "BallSpeedModel.h"


extern bool IS_SIMULATION;

namespace{
    bool isNearPlayer = false;
    bool isEnemyTouch = false;
    bool isOurTouch = false;


    int standOffCouter=0;
    int ourBallCouter=0;


    int lastTheirBestPlayer=0;
    int lastOurBestPlayer=0;
    const int StateMaxNum=5;
    int stateCouter[StateMaxNum]={0,0,0,0,0};

    auto pm = ParamManager::Instance();
}

CBallStatus::CBallStatus(void)
{
    _ballMovingVel = CVector(0,0);
    _isKickedOut = false;
    _ballToucher = 0;
    _kickerNum = 0;
    _ballState= None;
    _ballStateCouter=0;

    standOffCouter=0;
    ourBallCouter=0;

    initializeCmdStored();
}

void CBallStatus::UpdateBallStatus(const CVisionModule* pVision)
{
    // UpdateBallMoving(pVision);
    CheckKickOutBall(pVision);
    // if (_isKickedOut)
    //     qDebug() << "isKickedOut" << _isKickedOut << "isChipKickOut" << _isChipKickOut << "kickerNum" << _kickerNum;
    // _contactChecker.refereeJudge(pVision);
    _lastBallToucher = _ballToucher;
    // _ballToucher = _contactChecker.getContactNum();
    // if (_isKickedOut || _isChipKickOut){
    //     _ballToucher = _kickerNum;
    // }
    updateBallPossession(pVision);
}
// 更新球的所有权
void CBallStatus::updateBallPossession(const CVisionModule* pVision)
{
    // 判断我们的球员，使用视觉和红外，进入可吸球范围内
    computeBallPossession(pVision, true, pm->maxFrame, pm->ourVisionJudgeDist, pm->ourVisionJudgeDir, true);
    // 判断对方球员，只用视觉，表示离球较近
    computeBallPossession(pVision, false, pm->maxFrame, pm->theirVisionJudgeDist, pm->theirVisionJudgeDir, false);
    // 踢球后重置
    if (_isKickedOut) {
        ballPossession[_kickerNum] = 0;
        _ballToucher = _kickerNum;
    }
    else {
        int maxBallPossession = 0;
        // 如果我们有球员已经拿到了球，不管对方，就是我们的球
        for (int i = 0; i < Param::Field::MAX_PLAYER; i++) {
            if (ballPossession[i] > maxBallPossession) {
                maxBallPossession = ballPossession[i];
                _ballToucher = i;
            }
        }
        // 我们没有拿到球，看对方是否进入拿球的范围内
        if (maxBallPossession == 0) {
            for (int i = Param::Field::MAX_PLAYER; i < Param::Field::MAX_PLAYER * 2; i++) {
                if (ballPossession[i] > maxBallPossession) {
                    maxBallPossession = ballPossession[i];
                    _ballToucher = i;
                }
            }
        }
        // 大家都没有球，维持上一帧的触球者
    }
}

void CBallStatus::computeBallPossession(const CVisionModule* pVision, bool isOurPlayer, int maxFrame, double distThreshold, double dirThreshold, bool useInfrared)
{
    const BallVisionT& ball = pVision->Ball();
    for (int id = 0; id < Param::Field::MAX_PLAYER; id++) {
        PlayerVisionT player;
        if (isOurPlayer)
            player = pVision->OurPlayer(id);
        else
            player = pVision->TheirPlayer(id);
        // 视觉判断
        bool distVisionHasBall = CVector(player.Pos() - ball.Pos()).mod() <= distThreshold;
        bool dirVisionHasBall;
        double playerDir = player.Dir();
        double player2Ball = (ball.Pos() - player.Pos()).dir();
        double playerDir_player2Ball_Diff = fabs(Utils::Normalize((playerDir - player2Ball)));
        if (playerDir_player2Ball_Diff < dirThreshold * Param::Math::PI / 180.0)
            dirVisionHasBall = true;
        else
            dirVisionHasBall = false;
        bool isVisionPossession = dirVisionHasBall && distVisionHasBall;
        // 红外判断
        bool isInfraredPossession = false;
        if (isOurPlayer && useInfrared && RobotSensor::Instance()->IsInfraredOn(id))
            isInfraredPossession = true;
        // 综合判断及维持稳定
        int num = id + Param::Field::MAX_PLAYER * (1 - (int)isOurPlayer);
        if (isVisionPossession || isInfraredPossession)  // Attention!!!!   23.7.1 Modify By Tyh : 必须两者兼有才能判断已经get到球？ 打脸了
            ballPossession[num]++;
        else
            ballPossession[num] --;
        ballPossession[num] = max(0, min(maxFrame, ballPossession[num]));
    }
}
// 返回值的意义类似一个可信度
double CBallStatus::getBallPossession(bool isOurPlayer, int id) {
    int num = id + Param::Field::MAX_PLAYER * (1 - (int)isOurPlayer);
    if (id == 1) {
        char msg[100];
        sprintf(msg, "%f", (ballPossession[num] * 1.0 / pm->maxFrame));
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(270, -250), msg, COLOR_YELLOW);
    }
    return (ballPossession[num] * 1.0 / pm->maxFrame);
}

void CBallStatus::UpdateBallMoving(const CVisionModule* pVision)
{
    const BallVisionT& ball = pVision->Ball(); // 球
    isNearPlayer = false;
    for (int i=0; i<Param::Field::MAX_PLAYER*2; i++){
        if (pVision->AllPlayer(i).Valid() && pVision->AllPlayer(i).Pos().dist(ball.Pos())< Param::Field::MAX_PLAYER_SIZE/2+5){
            isNearPlayer = true;
            break;
        }
    }
    if (false == isNearPlayer && ball.Vel().mod()>2){
        // 只有当球不在车附近时,才使用预测后的球速来更新; 以免球在车附近时,将球速设为0;
        _ballMovingVel = ball.Vel();
    }
    else{
        // 保留球速，方向使用稳定可靠的方向
        double ballspeed = max(1.0, ball.Vel().mod());
        _ballMovingVel = Utils::Polar2Vector(ballspeed, _ballMovingVel.dir());
        //std::cout<<"BallStatus: Ball Near Player"<<endl;
    }
}

// 从PlayInterface中移出的球状态部分
void CBallStatus::initializeCmdStored()
{
    for (int i=0; i<Param::Field::MAX_PLAYER; i++){
        for (int j=0; j<MAX_CMD_STORED; j++){
            _kickCmd[i][j].setKickCmd(i,0,0,0);
        }
    }
}

// void CBallStatus::setCommand(CSendCmd kickCmd, int cycle)
// {
//     _kickCmd[kickCmd.num()][cycle % MAX_CMD_STORED] = kickCmd;
// }
void CBallStatus::setCommand(int num, int normalKick, int chipKick, unsigned char dribble, int cycle)
{
    _kickCmd[num][cycle % MAX_CMD_STORED].setKickCmd(num, normalKick, chipKick, dribble);
}

void CBallStatus::clearKickCmd()
{
    for (int i=0; i<Param::Field::MAX_PLAYER; i++){
        for (int j=0; j<MAX_CMD_STORED; j++){
            _kickCmd[i][j].clear();
        }
    }
}

void CBallStatus::detectKickOutOnVision(const CVisionModule* pVision, int playerID)
{
    const BallVisionT& ball = pVision->Ball();
    const PlayerVisionT& player = pVision->AllPlayer(playerID);
    CVector player2ball = ball.Pos() - player.Pos();
    double ballSpeedDir = ball.Vel().dir();
    double ballLeavingAngle = fabs(Utils::Normalize(ballSpeedDir - player2ball.dir()));
    double ballFleeingRelDir = fabs(Utils::Normalize(ballSpeedDir - player.Dir()));
    // 球离去的方向与车球朝向应该小于一定角度
    if (ballLeavingAngle < Param::Math::PI / 3 && ball.Vel().mod() > 100 && ballFleeingRelDir < Param::Math::PI / 12) {
        _isKickedOut = true;
        _kickerNum = playerID;
    }
}

void CBallStatus::CheckKickOutBall(const CVisionModule* pVision)
{
    _isKickedOut = false;
    _isChipKickOut = false;
    //std::cout << "This is Checkout.\n";
    for (int num = 0; num < Param::Field::MAX_PLAYER * 2; num++){
        // 仿真中也接入了红外和其他反馈，统一用视觉和反馈判断 -- 2023.4.25 yjz
        // 之前要先拿到球
        // if (ballPossession[num] == 0)
        //     continue;
        if (num >= Param::Field::MAX_PLAYER) {
            // 对于对方，只能拿视觉信息判断是否踢出
            detectKickOutOnVision(pVision, num);
            if (_isKickedOut)
                break;
        }
        else {
            // 查阅历史指令，考虑下发指令有延时，但没法确定执行的是那一条指令
            bool isKickCmdSent = false;
            for (int i = 0; i < MAX_CMD_STORED; i++) {
                CSendCmd kickCmd = getKickCommand(num, (pVision->Cycle() + MAX_CMD_STORED - i) % MAX_CMD_STORED);
                if (kickCmd.normalKick() > 0) {
                    isKickCmdSent = true;
                }
                else if (kickCmd.chipKick() > 0) {
                    _isChipKickOut = true; // 记录挑球标签
                }
            }
            // 之前应该发过踢球指令，否则不可能踢出
            if (isKickCmdSent || _isChipKickOut) {
                detectKickOutOnVision(pVision, num);
                // 考虑机器人的反馈，丢包和延时比较明显，作为视觉的补充
                bool sensorValid = RobotSensor::Instance()->IsInfoValid(num);
                int isKickDeviceOn = RobotSensor::Instance()->IsKickerOn(num);
                if (!_isKickedOut) {
                    if (sensorValid && isKickDeviceOn > 0) { // 视觉判为没踢但有踢球反馈，核实踢球反馈与指令是否匹配
                        // 防止是敌方堵在嘴部导致没踢出去，让球离开一段距离再确认
                        double ballLeaveDist = pVision->Ball().Pos().dist(pVision->OurPlayer(num).Pos());
                        _isKickedOut = ((isKickCmdSent && isKickDeviceOn == 1) || (_isChipKickOut && isKickDeviceOn == 2)) && ballLeaveDist > 50;
                        if (_isKickedOut) {
                            _isChipKickOut = _isChipKickOut && (isKickDeviceOn == 2);
                            _kickerNum = num;
                            break;
                        }
                    }
                }
                else {
                    if (isKickCmdSent && _isChipKickOut) // 同时有平射和挑球指令时，核实挑球标签
                        _isChipKickOut = sensorValid && isKickDeviceOn == 1 ? false : true;
                    break;
                }
            }
        }
        /************************************************************************/
        /*  优先利用双向通讯信息 [6/16/2011 cliffyin]		                    */
        /************************************************************************/
        // 实物: 优先检测上传信息
        // 实车通信不稳定，也使用仿真方法进行判断
        // if (! IS_SIMULATION && false) {
        //    bool sensorValid = RobotSensor::Instance()->IsInfoValid(num);
        //    bool isBallInFoot = RobotSensor::Instance()->IsInfraredOn(num);
        //    int isKickDeviceOn = RobotSensor::Instance()->IsKickerOn(num);
            // std::cout << "sensorValid: " << sensorValid << ", isBallInFoot: " << isBallInFoot << ", isKickDeviceOn: " << isKickDeviceOn << ".\n";
            // 用于双向通迅出现问题时，且此时红外正常
        //    if (sensorValid && isKickDeviceOn > 0) {
        //        _kickerNum = num;
        //        _isKickedOut = true;
        //        if (isKickDeviceOn == IS_CHIP_KICK_ON) {
        //            _isChipKickOut = true;
        //        }
        //        break;
        //    }
        // }
        // 仿真: 完全按照图像进行判断
        // else{
        //    bool isKickCmdSent = false;
        //    for (int i=0; i < MAX_CMD_STORED; i++){
        //        CSendCmd kickCmd = getKickCommand( num, (pVision->Cycle()+MAX_CMD_STORED-i) % MAX_CMD_STORED );
        //        if (kickCmd.normalKick()>0){
        //            isKickCmdSent = true;
        //        }
        //        else if (kickCmd.chipKick()>0){
        //            isKickCmdSent = true;
        //            _isChipKickOut = true; // 记录挑球标签
        //        }
        //    }
            //std::cout << "isKickCmdSent: " << isKickCmdSent << std::endl;
        //    if (false == isKickCmdSent){
        //        _isKickedOut = false;
        //        continue;
        //    }

        //    const BallVisionT& ball = pVision->Ball();
        //    const PlayerVisionT& player = pVision->OurPlayer(num);
        //    CVector player2ball = ball.Pos() - player.Pos();
        //    double ballSpeedDir = ball.Vel().dir();
        //    double ballLeavingAngle = fabs(Utils::Normalize(ballSpeedDir - player2ball.dir()));
        //    double ballFleeingRelDir = fabs(Utils::Normalize(ballSpeedDir - player.Dir()));

            // 球离去的方向与车球朝向应该小于一定角度
            //std::cout << "isKick:" << (ballLeavingAngle < Param::Math::PI / 3) << " " << (ball.Vel().mod() > 100) << " " << (ballFleeingRelDir < Param::Math::PI / 12) << "\n";
        //    if (ballLeavingAngle < Param::Math::PI / 3 && ball.Vel().mod() > 100
        //        &&  ballFleeingRelDir < Param::Math::PI/12){
        //        _isKickedOut = true;
        //        _kickerNum = num;
        //        break;
        //    }
        // }


        ///************************************************************************/
        ///*  然后图像判断 球是否有被踢出                                         */
        ///************************************************************************/
        //// 判断球踢出的几个标准:
        //const BallVisionT& ball = pVision->Ball();
        //const PlayerVisionT& player = pVision->OurPlayer(num);
        //CVector player2ball;
        //if (ball.Valid() && player.Valid()){
        //	player2ball = ball.Pos()-player.Pos();
        //}
        //else{
        //	// 车或球找不到
        //	_isKickedOut = false;
        //	continue;
        //}

        //// 0. 一定历史时间内,车是否发过射门指令
        //bool isKickCmdSent = false;
        //_isChipKickOut = false; // 重置挑球标签
        //for (int i=0; i<MAX_CMD_STORED; i++){
        //	CSendCmd kickCmd = getKickCommand( num, (pVision->Cycle()+MAX_CMD_STORED-i) % MAX_CMD_STORED );
        //	if (kickCmd.normalKick()>0){
        //		isKickCmdSent = true;
        //	}
        //	else if (kickCmd.chipKick()>0){
        //		isKickCmdSent = true;
        //		_isChipKickOut = true; // 记录挑球标签
        //	}
        //}
        //if (false == isKickCmdSent){
        //	_isKickedOut = false;
        //	continue;
        //}
        //else{
        //	//std::cout<<"Chk KickOut Ball: kick cmd from player: "<<num<<endl;
        //}

        //// 1.球离车而去
        //bool ballFleeing = false;
        //double ballSpeedDir = ball.Vel().dir();
        //double ballLeavingAngle = Utils::Normalize(ballSpeedDir - player2ball.dir());
        //if (ballLeavingAngle < Param::Math::PI/3){
        //	ballFleeing = true;
        //}

        //// 2. 球不是从身体其他部位碰出

        //double ballFleeingRelDir = Utils::Normalize(ballSpeedDir - player.Dir());
        //if ( (false == ballFleeing || std::abs(ballFleeingRelDir) > Param::Math::PI/12) && !isKickingNow){
        //	// 球不是离车而去,或从车非正面弹出.
        //	//		std::cout<<"num:"<<num<<" ball not fleeing"<<endl;
        //	_isKickedOut = false;
        //	continue;
        //}

        //if ( ball.Vel().mod() < 200){
        //	//		std::cout<<"num:"<<num<<" ball vel is too small"<<endl;
        //	_isKickedOut = false;
        //	continue;
        //}

        //if (player2ball.mod() < 50){
        //	//	std::cout<<"num:"<<num<<" ball is near player"<<endl;
        //	_isKickedOut = false;
        //	continue;
        //}

        //// 的确踢出球了,重置变量与标签
        ////cout<<"VisionOut    :  "<<num<<endl;
        //_isKickedOut = true;
        //_kickerNum = num;
        ////		 std::cout<<"CheckKickOutBall: kicked Out! chip: "<<_isChipKickOut<<endl;
        //break;
    }
}


void CBallStatus::clearBallStateCouter(){
    memset(stateCouter,0,StateMaxNum*sizeof(int));
    _ballState=None;
}

void subStateJudge(int i,int* stateCouter,bool* enterCond,int* keepThreshold,int& _ballState){
    if (!enterCond[i]){
        stateCouter[i]--;
        if (stateCouter[i]==0){
            _ballState=None;
            memset(stateCouter,0,StateMaxNum*sizeof(int));
        }
    }else{
        _ballState = i;
        stateCouter[i]++;
        stateCouter[i]=min(stateCouter[i],keepThreshold[i]);
    }
}

string CBallStatus::checkBallState(const CVisionModule* pVision,int meNum){
    const BallVisionT& ball=pVision->Ball();
    const CGeoPoint rawBallPos=pVision->Ball().Pos();
    int ourAdvancerNum=meNum;
    if (! Utils::PlayerNumValid(ourAdvancerNum)) {
        ourAdvancerNum = BestPlayer::Instance()->getOurBestPlayer();
        if (! Utils::PlayerNumValid(ourAdvancerNum)) {
            ourAdvancerNum = 1;
        }
    }
    int theirAdvancerNum= DefenceInfoNew::Instance()->getBestBallChaser();
    if (! Utils::PlayerNumValid(theirAdvancerNum)){
        theirAdvancerNum=NormalPlayUtils::getTheirMostClosetoPos(pVision,pVision->OurPlayer(meNum).Pos());
    }


    //cout<<ourAdvancerNum<<" "<<theirAdvancerNum<<endl;

    if (!ball.Valid()){
        ourAdvancerNum=lastOurBestPlayer;
        theirAdvancerNum=lastTheirBestPlayer;
    }

    PlayerVisionT me=pVision->OurPlayer(ourAdvancerNum);
    PlayerVisionT he=pVision->TheirPlayer(theirAdvancerNum);
    double meSpeed=pVision->OurRawPlayerSpeed(ourAdvancerNum).mod();
    double heSpeed=pVision->TheirRawPlayerSpeed(theirAdvancerNum).mod();
    double balltoMeDist=rawBallPos.dist(me.Pos());
    double balltoHeDist=rawBallPos.dist(he.Pos());
    double metoHeDist=me.Pos().dist(he.Pos());
    double metoHeDir=(he.Pos()-me.Pos()).dir();

    const double ballSpeed=ball.Vel().mod();
    const double ballVelDir = ball.Vel().dir();
    const CVector self2ball = rawBallPos - me.Pos();
    const CVector he2ball=rawBallPos - he.Pos();
    const CVector ball2self = me.Pos() -rawBallPos;
    const CVector ball2he =he.Pos() - rawBallPos;
    const double dist2ball=self2ball.mod();
    const double distHe2ball=he2ball.mod();

    const double dAngleMeBall2BallVelDir = fabs(Utils::Normalize(ball2self.dir() - ballVelDir));	//球车向量与球速线夹角
    const CGeoSegment ballMovingSeg = CGeoSegment(rawBallPos+Utils::Polar2Vector(10,Utils::Normalize(ballVelDir)),rawBallPos+Utils::Polar2Vector(800,Utils::Normalize(ballVelDir)));
    const CGeoPoint projMe = ballMovingSeg.projection(me.Pos());					//小车在球移动线上的投影点
    double projDist = projMe.dist(me.Pos());

    const CGeoSegment balltoMeSeg = CGeoSegment(rawBallPos+Utils::Polar2Vector(20,Utils::Normalize(ballVelDir)),rawBallPos+Utils::Polar2Vector(dist2ball+30,Utils::Normalize(ballVelDir)));
    const CGeoPoint projHe = ballMovingSeg.projection(he.Pos());
    double projDistHe =projHe.dist(he.Pos());

    double antiHeDir=Utils::Normalize(he.Dir()+Param::Math::PI);
    const double shootDir=KickDirection::Instance()->getRealKickDir();
    CGeoPoint predictBallPos=BallSpeedModel::Instance()->posForTime(30,pVision);

    const double metoBallAngle=(rawBallPos-me.Pos()).dir();
    const double antiMetoBallAngle=(me.Pos()-rawBallPos).dir();
    const CGeoSegment metoBallSeg=CGeoSegment(me.Pos()+Utils::Polar2Vector(10,antiMetoBallAngle),me.Pos()+Utils::Polar2Vector(100,metoBallAngle));
    const CGeoPoint projHeInMetoBallSeg=metoBallSeg.projection(he.Pos());
    const CGeoPoint meHead=me.Pos()+Utils::Polar2Vector(Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER,me.Dir());
    //isOurBall
    double diffAngleMeToBall2Me=fabs(Utils::Normalize(me.Dir()-metoBallAngle));
    double allowInfrontAngleBuffer = (dist2ball/(Param::Vehicle::V2::PLAYER_SIZE))*Param::Vehicle::V2::KICK_ANGLE < Param::Math::PI/5.0?
        (dist2ball/(Param::Vehicle::V2::PLAYER_SIZE))*Param::Vehicle::V2::KICK_ANGLE:Param::Math::PI/5.0;
    double allowInfrontAngleBufferHe = (distHe2ball/(Param::Vehicle::V2::PLAYER_SIZE))*Param::Vehicle::V2::KICK_ANGLE < Param::Math::PI/5.0?
        (distHe2ball/(Param::Vehicle::V2::PLAYER_SIZE))*Param::Vehicle::V2::KICK_ANGLE:Param::Math::PI/5.0;

    bool isBallInFront = fabs(Utils::Normalize(self2ball.dir()-me.Dir())) < allowInfrontAngleBuffer
        && dist2ball < (2.5*Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE);
    bool isBallInHeFront =fabs(Utils::Normalize(he2ball.dir()-he.Dir())) < allowInfrontAngleBufferHe
        && distHe2ball < (dist2ball+Param::Vehicle::V2::PLAYER_SIZE + Param::Field::BALL_SIZE);

    bool isBallJustInFront=ball.Vel().mod()<10 && fabs(Utils::Normalize(self2ball.dir()-me.Dir()))<Param::Math::PI/15
        && meHead.dist(rawBallPos)<8 && fabs(me.Dir())<Param::Math::PI/3;

    bool isHeInMeFront = fabs(Utils::Normalize(metoHeDir-me.Dir())) < Param::Math::PI/3
        && metoHeDist <dist2ball+4*Param::Vehicle::V2::PLAYER_SIZE ;

    bool isBallMovtoMe=ballSpeed<400&&ballSpeed>120&&(dAngleMeBall2BallVelDir<Param::Math::PI/4||projDist<50)
        &&ballMovingSeg.IsPointOnLineOnSegment(projMe)&&projMe.dist(rawBallPos)>30
        &&NormalPlayUtils::noEnemyInPassLine(pVision,rawBallPos,me.Pos(),20);

    bool isBallMovtoHe=balltoMeSeg.IsPointOnLineOnSegment(projHe)&&projDistHe<projDist+35&&Utils::Normalize(antiHeDir-ball.Vel().dir())<Param::Math::PI/3;


    //standOff
    bool isHeFrontToMe=fabs(Utils::Normalize(me.Dir()-antiHeDir))<Param::Math::PI/3&&me.Pos().dist(he.Pos())<40;
    bool isMeHeStandOff=isHeFrontToMe&&me.Pos().dist(he.Pos())<35;
    bool isStandOff=(ball.Valid()&&ballSpeed<50&&isBallInFront&&self2ball.mod()<15||!ball.Valid())&&isMeHeStandOff
        ||(me.Pos().dist(he.Pos())<35&&ballSpeed<30&&(metoBallSeg.IsPointOnLineOnSegment(projHeInMetoBallSeg)||diffAngleMeToBall2Me>Param::Math::PI/2));
    int judgeRange=30;
    if (dist2ball>150){
        judgeRange=50;
    }else if (dist2ball>80){
        judgeRange=40;
    }else if (dist2ball>30){
        judgeRange=30;
    }else{
        judgeRange=25;
    }


    bool canGiveUpAdvance=getBallToucher()>=Param::Field::MAX_PLAYER
        &&ball.Vel().mod()>80&&Utils::OutOfField(predictBallPos,-10)
        &&fabs(ball.Vel().dir())>Param::Math::PI*80/180
        &&he.Pos().dist(rawBallPos)>me.Pos().dist(rawBallPos)+30
        &&!NormalPlayUtils::isEnemyFrontToBall(pVision,30)
        &&!NormalPlayUtils::ballMoveToOurDefendArea(pVision)
        //&&me.Pos().dist(rawBallPos)/200>0.5
        ;


    double heSpeedInBallVel=heSpeed*cos(Utils::Normalize(he.Vel().dir()-ball.Vel().dir()))*1.5;
    bool notHeGetBallBefore=projDistHe>projDist+35||Utils::Normalize(he2ball.dir()-he.Dir())>Param::Math::PI/2;
    if (balltoMeSeg.IsPointOnLineOnSegment(projHe)){
        notHeGetBallBefore=notHeGetBallBefore||projDist/ballSpeed<projDistHe/(ballSpeed+heSpeedInBallVel);
    }else if(!ballMovingSeg.IsPointOnLineOnSegment(projHe)){
        notHeGetBallBefore=notHeGetBallBefore||projDist/ballSpeed<projDistHe/(ballSpeed-heSpeedInBallVel);
    }else{
        notHeGetBallBefore=true;
    }

    int closedHeNum=NormalPlayUtils::getTheirMostClosetoPos(pVision,ball.Pos());
    CGeoPoint theirClosedCar=pVision->TheirPlayer(closedHeNum).Pos();
    bool isOurBall=ball.Valid()&&
        (isBallMovtoMe && notHeGetBallBefore
            ||isBallJustInFront&&!isHeFrontToMe
            ||(!canGiveUpAdvance&&!isBallInHeFront
            &&(balltoHeDist-balltoMeDist>judgeRange || balltoHeDist>balltoMeDist+15 && isBallInFront)
            &&ball.Pos().dist(theirClosedCar)>balltoMeDist+15
            )
        );
    //cout<<isBallMovtoMe<<" "<<isBallJustInFront<<" "<<isHeFrontToMe<<" "<<isBallInHeFront<<endl;
    //waitTouch
    bool canWaitAdvance=ballSpeed>350&&fabs(ballVelDir)<Param::Math::PI/3;
    canWaitAdvance=false;
    //giveUpAdvance


    //cout<<"canGive"<<" "<<canGiveUpAdvance<<endl;


    //memset(stateCouter,0,StateMaxNum*sizeof(int));
    int jumpThreshold[StateMaxNum];
    jumpThreshold[None]=0;
    jumpThreshold[OurBall]=5;
    jumpThreshold[StandOff]=15;
    jumpThreshold[WaitAdvance]=5;
    jumpThreshold[GiveUpAdvance]=5;

    int keepThreshold[StateMaxNum];
    keepThreshold[None]=0;
    keepThreshold[OurBall]=8;
    keepThreshold[StandOff]=45;
    keepThreshold[WaitAdvance]=5;
    keepThreshold[GiveUpAdvance]=10;

    bool enterCond[StateMaxNum];
    enterCond[None]=false;
    enterCond[OurBall]=isOurBall;
    enterCond[StandOff]=isStandOff&&!isOurBall;
    enterCond[WaitAdvance]=canWaitAdvance;
    enterCond[GiveUpAdvance]=canGiveUpAdvance;
    switch (_ballState)
    {
    case None:
        //if (IsBallKickedOut()&&fabs(Utils::Normalize(me.Dir()-shootDir))<Param::Math::PI/10){
        //	memset(stateCouter,0,StateMaxNum*sizeof(int));
        //	stateCouter[WaitAdvance]=keepThreshold[WaitAdvance];
        //	_ballState=WaitAdvance;
        //	break;
        //}
        for (int i=1;i<StateMaxNum;i++){
            if (enterCond[i]){
                stateCouter[i]++;
                if (stateCouter[i]>=jumpThreshold[i]){
                    memset(stateCouter,0,StateMaxNum*sizeof(int));
                    stateCouter[i]=keepThreshold[i];
                    _ballState=i;
                    break;
                }
            }else{
                stateCouter[i]--;
                stateCouter[i]=max(stateCouter[i],0);
            }
        }
        break;
    case OurBall:
        //if (IsBallKickedOut()&&fabs(Utils::Normalize(me.Dir()-shootDir))<Param::Math::PI/10){
        //	memset(stateCouter,0,StateMaxNum*sizeof(int));
        //	stateCouter[WaitAdvance]=keepThreshold[WaitAdvance];
        //	_ballState=WaitAdvance;
        //	break;
        //}
        subStateJudge(OurBall,stateCouter,enterCond,keepThreshold,_ballState);
        break;
    case StandOff:
        if (world->IsBestPlayerChanged()/*||IsBallKickedOut()*/){
            _ballState=None;
            memset(stateCouter,0,StateMaxNum*sizeof(int));
            break;
        }
        subStateJudge(StandOff,stateCouter,enterCond,keepThreshold,_ballState);
        break;
    case WaitAdvance:
        if (ballToucherChanged()){
            _ballState=None;
            memset(stateCouter,0,StateMaxNum*sizeof(int));
            break;
        }
        subStateJudge(WaitAdvance,stateCouter,enterCond,keepThreshold,_ballState);
        break;
    case GiveUpAdvance:
        subStateJudge(GiveUpAdvance,stateCouter,enterCond,keepThreshold,_ballState);
        break;
    }
    if (ball.Valid()){
        lastTheirBestPlayer= DefenceInfoNew::Instance()->getBestBallChaser();
        lastOurBestPlayer=BestPlayer::Instance()->getOurBestPlayer();
    }
    switch(_ballState){
    case OurBall:
        return "OurBall";
    case None:
        return "None";
    case StandOff:
        return "StandOff";
    case WaitAdvance:
        return "WaitAdvance";
    case GiveUpAdvance:
        return "GiveUpAdvance";
    }
}
