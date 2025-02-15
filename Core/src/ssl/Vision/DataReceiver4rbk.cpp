#include "DataReceiver4rbk.h"
#include "vision_detection.pb.h"
#include "src_rawvision.pb.h"
#include "utils.h"
#include "OptionModule.h"
#include "game_state.h"
#include <thread>
#include <QMutex>
#include <QNetworkProxy>
#include <QNetworkInterface>
#include "ParamManagerNew.h"
#include "Semaphore.h"
extern bool IS_SIMULATION;
Semaphore visionEvent;
namespace {
    Vision_DetectionFrame rec_vision;
    std::thread* receive_vision_thread;
    std::thread* referee_thread;
    QMutex receive_vision_mutex;
    QMutex referee_mutex;
    QUdpSocket* receive_vision_socket;
    int isYellow;
    GameInfoT visionInfo;
    GameInfoT refereeInfo;
	struct sCMD_TYPE {
		char cmd;
		unsigned int step;
	};
	struct stGamePacket {
		char cmd;
        char next_cmd;
		unsigned char cmd_counter;
		unsigned char goals_blue;
		unsigned char goals_yellow;
		unsigned short time_remaining;
	};
	float msgX2InfoX(float x) { return (x/10.0); }
	float msgY2InfoY(float y) { return (-y/10.0); }
    float msgAngle2InfoAngle(float angle) { return -angle; }
}
CDataReceiver4rbk::CDataReceiver4rbk():referee_socket(){
    refereeInfo.mode = m_play_mode = PMNone;
    auto pOption = new COptionModule();
    isYellow = pOption->MyColor();
    delete pOption;
    int vision_port = (isYellow == TEAM_YELLOW) ? CParamManager::Instance()->yellow_vision : CParamManager::Instance()->blue_vision;
    int referee_port = isYellow == TEAM_YELLOW ? OParamManager::Instance()->refereePortToYellow : OParamManager::Instance()->refereePortToBlue;
    qDebug() << referee_port;
    referee_socket.setProxy(QNetworkProxy::NoProxy);
    referee_socket.bind(QHostAddress::AnyIPv4, referee_port, QUdpSocket::ShareAddress);
    referee_socket.joinMulticastGroup(QHostAddress(CParamManager::Instance()->referee_address)); // receive Athena ref, need to change ZSS_ADDRESS
    //foreach (const QNetworkInterface& iface, QNetworkInterface::allInterfaces()) {
    //    referee_socket.joinMulticastGroup(QHostAddress(CParamManager::Instance()->referee_address), iface);
    //}
    // 这是昨晚的表述 referee_socket.joinMulticastGroup(QHostAddress(CParamManager::Instance()->referee_address)); // receive Athena ref, need to change ZSS_ADDRESS
    //这是之前的表述 我已经恢复foreach (const QNetworkInterface& iface, QNetworkInterface::allInterfaces()) {
    //    referee_socket.joinMulticastGroup(QHostAddress(CParamManager::Instance()->referee_address), iface);
    //}
    referee_thread = new std::thread([=] {receiveRefMsgs();});
    referee_thread->detach();
    receive_vision_socket = new QUdpSocket();
    receive_vision_socket->bind(QHostAddress::AnyIPv4, vision_port, QUdpSocket::ShareAddress);
    receive_vision_thread = new std::thread([=] {receiveVision();});
    receive_vision_thread->detach();
}

CDataReceiver4rbk::~CDataReceiver4rbk(void) {
    //delete referee_socket;
    //referee_socket = nullptr;
    referee_socket.abort();
    delete receive_vision_socket;
    receive_vision_socket = nullptr;
    delete referee_thread;
    referee_thread = nullptr;
    delete receive_vision_thread;
    receive_vision_thread = nullptr;
}

void CDataReceiver4rbk::receiveVision() {
    QByteArray buffer;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        while (receive_vision_socket->state() == QUdpSocket::BoundState && receive_vision_socket->hasPendingDatagrams()) {
            buffer.resize(receive_vision_socket->pendingDatagramSize());
            receive_vision_socket->readDatagram(buffer.data(), buffer.size());
            receive_vision_mutex.lock();
            rec_vision.ParseFromArray(buffer, buffer.size());
            receive_vision_mutex.unlock();
            visionEvent.Signal();
        }
    }
}

bool CDataReceiver4rbk::rawVision2VisualInfo(const COptionModule *pOption,GameInfoT& info){
	/** GameInfo包括视觉信息和裁判信息，之后要加上方差等信息,player的信息全部加载进来，用于robot predictor **/
    static int last_cycle = 0;
    static int strategy_cycle = 0;
    bool receive_new_vision = false;
    static Vision_DetectionFrame vision;
    receive_vision_mutex.lock();
    vision = rec_vision;
    receive_vision_mutex.unlock();
    if (vision.has_login_name() && vision.login_name() != OParamManager::Instance()->LoginName) // 串频问题
        return false;
    info.cycle = ++strategy_cycle;
    info.mode = m_play_mode;
    info.ball.pos.valid = vision.has_balls() ? vision.balls().valid() : false;
    if (info.ball.pos.valid) {
        auto& ball = vision.balls();
        info.ball.pos.x = msgX2InfoX(ball.x());
        info.ball.pos.y = msgY2InfoY(ball.y());
        info.ball.vel = CVector(msgX2InfoX(ball.vel_x()), msgY2InfoY(ball.vel_y()));
        info.ball.chipPredict.x = msgX2InfoX(ball.chip_predict_x());
        info.ball.chipPredict.y = msgY2InfoY(ball.chip_predict_y());
    }
    else {
        info.ball.pos.x = 9999;
        info.ball.pos.y = 9999;
        info.ball.vel = CVector(0, 0);
        info.ball.chipPredict.x = 9999;
        info.ball.chipPredict.y = 9999;
    }

    for (int i = 0; i < Param::Field::MAX_PLAYER * 2; i++) { // init vision
        info.player[i].dir = 0;
        info.player[i].pos.valid = 0;
        info.player[i].ID = -1;
        info.player[i].isYellow = true;
        info.player[i].pos.x = 9999;
        info.player[i].pos.y = 9999;
        info.player[i].vel = CVector(0, 0);
        info.player[i].acc = CVector(0, 0);
    }
    if (isYellow == TEAM_BLUE) {
        for (int i = 0; i < vision.robots_blue_size(); i++) {
            const Vision_DetectionRobot& robot = vision.robots_blue(i);
            if (!robot.valid()) continue;
            int id = robot.robot_id();
            info.player[id].dir = msgAngle2InfoAngle(robot.orientation());
            info.player[id].pos.valid = true;
            info.player[id].ID = robot.robot_id();
            info.player[id].isYellow = false;
            info.player[id].pos.x = msgX2InfoX(robot.x());
            info.player[id].pos.y = msgY2InfoY(robot.y());
            info.player[id].vel = CVector(msgX2InfoX(robot.vel_x()), msgY2InfoY(robot.vel_y()));
            info.player[id].acc = CVector(msgX2InfoX(robot.accelerate_x()), msgY2InfoY(robot.accelerate_y()));
            info.player[id].dirvel=robot.rotate_vel();
        }
        for (int i = 0; i < vision.robots_yellow_size(); i++) {
            const Vision_DetectionRobot& robot = vision.robots_yellow(i);
            if (!robot.valid()) continue;
            int id = robot.robot_id();
            info.player[Param::Field::MAX_PLAYER + id].dir = msgAngle2InfoAngle(robot.orientation());
            info.player[Param::Field::MAX_PLAYER + id].pos.valid = true;
            info.player[Param::Field::MAX_PLAYER + id].ID = robot.robot_id();
            info.player[Param::Field::MAX_PLAYER + id].isYellow = true;
            info.player[Param::Field::MAX_PLAYER + id].pos.x = msgX2InfoX(robot.x());
            info.player[Param::Field::MAX_PLAYER + id].pos.y = msgY2InfoY(robot.y());
            info.player[Param::Field::MAX_PLAYER + id].vel = CVector(msgX2InfoX(robot.vel_x()), msgY2InfoY(robot.vel_y()));
            info.player[Param::Field::MAX_PLAYER + id].acc = CVector(msgX2InfoX(robot.accelerate_x()), msgY2InfoY(robot.accelerate_y()));
            info.player[Param::Field::MAX_PLAYER + id].dirvel=robot.rotate_vel();
        }
    }
    else {
        for (int i = 0; i < vision.robots_yellow_size(); i++) {
            const Vision_DetectionRobot& robot = vision.robots_yellow(i);
            if (!robot.valid()) continue;
            int id = robot.robot_id();
            info.player[id].dir = msgAngle2InfoAngle(robot.orientation());
            info.player[id].pos.valid = true;
            info.player[id].ID = robot.robot_id();
            info.player[id].isYellow = true;
            info.player[id].pos.x = msgX2InfoX(robot.x());
            info.player[id].pos.y = msgY2InfoY(robot.y());
            info.player[id].vel = CVector(msgX2InfoX(robot.vel_x()), msgY2InfoY(robot.vel_y()));
            info.player[id].acc = CVector(msgX2InfoX(robot.accelerate_x()), msgY2InfoY(robot.accelerate_y()));
            info.player[id].dirvel =robot.rotate_vel();
        }
        for (int i = 0; i < vision.robots_blue_size(); i++) {
            const Vision_DetectionRobot& robot = vision.robots_blue(i);
            if (!robot.valid()) continue;
            int id = robot.robot_id();
            info.player[Param::Field::MAX_PLAYER + id].dir = msgAngle2InfoAngle(robot.orientation());
            info.player[Param::Field::MAX_PLAYER + id].pos.valid = true;
            info.player[Param::Field::MAX_PLAYER + id].ID = robot.robot_id();
            info.player[Param::Field::MAX_PLAYER + id].isYellow = false;
            info.player[Param::Field::MAX_PLAYER + id].pos.x = msgX2InfoX(robot.x());
            info.player[Param::Field::MAX_PLAYER + id].pos.y = msgY2InfoY(robot.y());
            info.player[Param::Field::MAX_PLAYER + id].vel = CVector(msgX2InfoX(robot.vel_x()), msgY2InfoY(robot.vel_y()));
            info.player[Param::Field::MAX_PLAYER + id].acc = CVector(msgX2InfoX(robot.accelerate_x()), msgY2InfoY(robot.accelerate_y()));
            info.player[Param::Field::MAX_PLAYER + id].dirvel=robot.rotate_vel();
        }
    }
    //info = visionInfo;
    //if (visionInfo.cycle > last_cycle) {
    //    last_cycle = visionInfo.cycle;
        receive_new_vision = true;
    //}
    
    return receive_new_vision;
}

void CDataReceiver4rbk::receiveRefMsgs() {
    Referee ssl_referee;
    QByteArray datagram;
    static unsigned char former_cmd_index = 0;
    static Referee_Command last_next_command = Referee_Command_HALT;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (referee_socket.state() == QUdpSocket::BoundState && referee_socket.hasPendingDatagrams()) {
            datagram.resize(referee_socket.pendingDatagramSize());
            referee_socket.readDatagram(datagram.data(), datagram.size());
            ssl_referee.ParseFromArray((void*)datagram.data(), datagram.size());
            //if (ssl_referee.has_login_name() && ssl_referee.login_name() != OParamManager::Instance()->LoginName)
            //    break;
            PlayMode next_play_mode = PMNone; // avoid next command is none
            if (ssl_referee.has_next_command()) { // check next command first
                Referee_Command next_command = ssl_referee.next_command();
                if (last_next_command != next_command) { // update next command
                    last_next_command = next_command;
                    next_play_mode = translateRefMsgs(next_command);
                    referee_mutex.lock();
                    refereeInfo.next_mode = next_play_mode;
                    referee_mutex.unlock();
                }
            }
            unsigned long command_counter = ssl_referee.command_counter();
            if (command_counter == former_cmd_index) continue;
            former_cmd_index = command_counter;	// 更新上一次指令得标志值
            //update refereemsg
            unsigned long long packet_timestamp = ssl_referee.packet_timestamp();
            Referee_Stage stage = ssl_referee.stage();
            Referee_Command command = ssl_referee.command();
            unsigned long long command_timestamp = ssl_referee.command_timestamp();
            Referee_TeamInfo yellow = ssl_referee.yellow();
            Referee_TeamInfo blue = ssl_referee.blue();
            long long stage_time_left = ssl_referee.stage_time_left();
            m_play_mode = translateRefMsgs(command);
            //qDebug() << command;
            referee_mutex.lock();
            // Get Ball Placement Position
            if (command == 16 || command == 17) {
                refereeInfo.refMsg.ballPlacement.x = msgX2InfoX(ssl_referee.designated_position().x());
                refereeInfo.refMsg.ballPlacement.y = msgY2InfoY(ssl_referee.designated_position().y());
                //std::cout << "Received ball placement pos : " << msg.ballPlacementX << " ,  " << msg.ballPlacementY << std::endl;
            }
            if( m_play_mode != PMNone ) {
                refereeInfo.mode = m_play_mode;
                refereeInfo.refMsg.blueGoal = (int)blue.score();
                refereeInfo.refMsg.yellowGoal = (int)yellow.score();
                refereeInfo.refMsg.blueGoalie = (int)blue.goalkeeper();
                refereeInfo.refMsg.yellowGoalie = (int)yellow.goalkeeper();
                refereeInfo.refMsg.timeRemain = stage_time_left / 1000000;
                static int cnt = 0;
                cnt++;
                if(cnt%100 == 0)std::cout << "Protobuf Protocol: RefereeBox Command : " << playModePair[m_play_mode].what << std::endl;
                //std::cout << "Stage_time_left : "<< msg.timeRemain << " Goals for blue : "<< (int)(pCmd_temp.goals_blue)
                //	<< " Goals for yellow : "<< (int)(pCmd_temp.goals_yellow) << std::endl;
            }
            referee_mutex.unlock();
        }
    }
}

PlayMode CDataReceiver4rbk::translateRefMsgs(Referee_Command command){
    char cmd;
    switch (command) {
    case 0: cmd = 'H'; break; // Halt
    case 1: cmd = 'S'; break; // Stop
    case 2: cmd = ' '; break; // Normal start (Ready)
    case 3: cmd = 's'; break; // Force start (Start)
    case 4: cmd = 'k'; break; // Kickoff Yellow
    case 5: cmd = 'K'; break; // Kickoff Blue
    case 6: cmd = 'p'; break; // Penalty Yellow
    case 7: cmd = 'P'; break; // Penalty Blue
    case 8: cmd = 'f'; break; // Direct Yellow
    case 9: cmd = 'F'; break; // Direct Blue
    case 10: cmd = 'i'; break; // Indirect Yellow
    case 11: cmd = 'I'; break; // Indirect Blue
    case 12: cmd = 't'; break; // Timeout Yellow
    case 13: cmd = 'T'; break; // Timeout Blue
    case 14: cmd = 'g'; break; // Goal Yellow
    case 15: cmd = 'G'; break; // Goal Blue
    case 16: cmd = 'b'; break; // Ball Placement Yellow
    case 17: cmd = 'B'; break; // Ball Placement Blue
    default:
        std::cout << "refereebox is fucked !!!!! command : " << command << std::endl;
        cmd = 'H'; break;
    }
    //std::cout << cmd << endl;
    PlayMode play_mode = PMNone;
    for( int pm = PMStop; pm <= PMNone; ++pm ) {
        if( playModePair[pm].ch == cmd ) {
            // 寻找匹配的指令名字
            play_mode = playModePair[pm].mode;
            break;
        }
    }
    return play_mode;
}

bool CDataReceiver4rbk::getNewRefMsgs(GameInfoT& info){
    referee_mutex.lock();
    info.mode = refereeInfo.mode;
    info.next_mode = refereeInfo.next_mode;
    info.refMsg = refereeInfo.refMsg;
    referee_mutex.unlock();
    return true;
}

bool CDataReceiver4rbk::getGameInfo(const COptionModule *pOption,GameInfoT& info){
    visionEvent.Wait();
    //get rawvision into visualinfo
	if (!rawVision2VisualInfo(pOption,info)){
		return false;
    }
    getNewRefMsgs(info);

	return true;
}
