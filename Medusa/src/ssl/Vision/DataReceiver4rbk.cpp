#include "DataReceiver4rbk.h"
#include "ssl_referee.pb.h"
#include "vision_detection.pb.h"
#include "src_rawvision.pb.h"
#include "utils.h"
#include "OptionModule.h"
#include "game_state.h"
#include <thread>
#include <QMutex>
#include <QNetworkProxy>
#include <QNetworkInterface>
#include "staticparams.h"
#include "parammanager.h"
extern bool IS_SIMULATION;
namespace {
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
	m_play_mode = PMNone;
    auto pOption = new COptionModule();
    isYellow = pOption->MyColor();
    delete pOption;
    int vision_port = ZSS::Athena::VISION_SEND[isYellow == TEAM_YELLOW ? PARAM::YELLOW : PARAM::BLUE];
    int referee_port;
    ZSS::ZParamManager::instance()->loadParam(referee_port, "AlertPorts/ZSS_RefereePort", 39991);
    if (IS_SIMULATION && isYellow == TEAM_YELLOW) referee_port += 1;
    //qDebug()<<"referee_port"<<referee_port;
    referee_socket.setProxy(QNetworkProxy::NoProxy);
    referee_socket.bind(QHostAddress::AnyIPv4, referee_port, QUdpSocket::ShareAddress);
    //referee_socket.joinMulticastGroup(QHostAddress(ZSS::REF_ADDRESS)); // receive Athena ref, need to change ZSS_ADDRESS
    foreach (const QNetworkInterface& iface, QNetworkInterface::allInterfaces()) {
        referee_socket.joinMulticastGroup(QHostAddress(ZSS::REF_ADDRESS), iface);
    }
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
    int strategy_cycle = 0;
    Vision_DetectionFrame vision;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        while (receive_vision_socket->state() == QUdpSocket::BoundState && receive_vision_socket->hasPendingDatagrams()) {
            buffer.resize(receive_vision_socket->pendingDatagramSize());
            receive_vision_socket->readDatagram(buffer.data(), buffer.size());
            vision.ParseFromArray(buffer, buffer.size());
            receive_vision_mutex.lock();
            visionInfo.cycle = ++strategy_cycle;
            visionInfo.mode = m_play_mode;
            visionInfo.ball.pos.valid = vision.has_balls();
            if (visionInfo.ball.pos.valid) {
                auto& ball = vision.balls();
                visionInfo.ball.pos.x = msgX2InfoX(ball.x());
                visionInfo.ball.pos.y = msgY2InfoY(ball.y());
                visionInfo.ball.vel = CVector(msgX2InfoX(ball.vel_x()), msgY2InfoY(ball.vel_y()));
                visionInfo.ball.chipPredict.x = msgX2InfoX(ball.chip_predict_x());
                visionInfo.ball.chipPredict.y = msgY2InfoY(ball.chip_predict_y());
            }
            else {
                visionInfo.ball.pos.x = 9999;
                visionInfo.ball.pos.y = 9999;
                visionInfo.ball.vel = CVector(0, 0);
                visionInfo.ball.chipPredict.x = 9999;
                visionInfo.ball.chipPredict.y = 9999;
            }

            for (int i = 0; i < Param::Field::MAX_PLAYER * 2; i++) { // init vision
                visionInfo.player[i].dir = 0;
                visionInfo.player[i].pos.valid = 0;
                visionInfo.player[i].ID = -1;
                visionInfo.player[i].isYellow = true;
                visionInfo.player[i].pos.x = 9999;
                visionInfo.player[i].pos.y = 9999;
                visionInfo.player[i].vel = CVector(0, 0);
                visionInfo.player[i].acc = CVector(0, 0);
            }
            if (isYellow == TEAM_BLUE){
                for(int i=0;i<vision.robots_blue_size();i++){
                    const Vision_DetectionRobot& robot = vision.robots_blue(i);
                    if (!robot.valid()) continue;
                    int id = robot.robot_id();
                    visionInfo.player[id].dir = msgAngle2InfoAngle(robot.orientation());
                    visionInfo.player[id].pos.valid = true;
                    visionInfo.player[id].ID = robot.robot_id();
                    visionInfo.player[id].isYellow = false;
                    visionInfo.player[id].pos.x = msgX2InfoX(robot.x());
                    visionInfo.player[id].pos.y = msgY2InfoY(robot.y());
                    visionInfo.player[id].vel = CVector(msgX2InfoX(robot.vel_x()), msgY2InfoY(robot.vel_y()));
                    visionInfo.player[id].acc = CVector(msgX2InfoX(robot.accelerate_x()), msgY2InfoY(robot.accelerate_y()));
                }
                for(int i=0;i<vision.robots_yellow_size();i++){
                    const Vision_DetectionRobot& robot = vision.robots_yellow(i);
                    if (!robot.valid()) continue;
                    int id = robot.robot_id();
                    visionInfo.player[Param::Field::MAX_PLAYER+id].dir = msgAngle2InfoAngle(robot.orientation());
                    visionInfo.player[Param::Field::MAX_PLAYER+id].pos.valid = true;
                    visionInfo.player[Param::Field::MAX_PLAYER+id].ID = robot.robot_id();
                    visionInfo.player[Param::Field::MAX_PLAYER+id].isYellow = true;
                    visionInfo.player[Param::Field::MAX_PLAYER+id].pos.x = msgX2InfoX(robot.x());
                    visionInfo.player[Param::Field::MAX_PLAYER+id].pos.y = msgY2InfoY(robot.y());
                    visionInfo.player[Param::Field::MAX_PLAYER+id].vel = CVector(msgX2InfoX(robot.vel_x()), msgY2InfoY(robot.vel_y()));
                    visionInfo.player[Param::Field::MAX_PLAYER+id].acc = CVector(msgX2InfoX(robot.accelerate_x()), msgY2InfoY(robot.accelerate_y()));
                }
            }else{
                for(int i=0;i<vision.robots_yellow_size();i++){
                    const Vision_DetectionRobot& robot = vision.robots_yellow(i);
                    if (!robot.valid()) continue;
                    int id = robot.robot_id();
                    visionInfo.player[id].dir = msgAngle2InfoAngle(robot.orientation());
                    visionInfo.player[id].pos.valid = true;
                    visionInfo.player[id].ID = robot.robot_id();
                    visionInfo.player[id].isYellow = true;
                    visionInfo.player[id].pos.x = msgX2InfoX(robot.x());
                    visionInfo.player[id].pos.y = msgY2InfoY(robot.y());
                    visionInfo.player[id].vel = CVector(msgX2InfoX(robot.vel_x()), msgY2InfoY(robot.vel_y()));
                    visionInfo.player[id].acc = CVector(msgX2InfoX(robot.accelerate_x()), msgY2InfoY(robot.accelerate_y()));
                }
                for(int i=0;i<vision.robots_blue_size();i++){
                    const Vision_DetectionRobot& robot = vision.robots_blue(i);
                    if (!robot.valid()) continue;
                    int id = robot.robot_id();
                    visionInfo.player[Param::Field::MAX_PLAYER+id].dir = msgAngle2InfoAngle(robot.orientation());
                    visionInfo.player[Param::Field::MAX_PLAYER+id].pos.valid = true;
                    visionInfo.player[Param::Field::MAX_PLAYER+id].ID = robot.robot_id();
                    visionInfo.player[Param::Field::MAX_PLAYER+id].isYellow = false;
                    visionInfo.player[Param::Field::MAX_PLAYER+id].pos.x = msgX2InfoX(robot.x());
                    visionInfo.player[Param::Field::MAX_PLAYER+id].pos.y = msgY2InfoY(robot.y());
                    visionInfo.player[Param::Field::MAX_PLAYER+id].vel = CVector(msgX2InfoX(robot.vel_x()), msgY2InfoY(robot.vel_y()));
                    visionInfo.player[Param::Field::MAX_PLAYER+id].acc = CVector(msgX2InfoX(robot.accelerate_x()), msgY2InfoY(robot.accelerate_y()));
                }
            }
            receive_vision_mutex.unlock();
        }
    }
}

bool CDataReceiver4rbk::rawVision2VisualInfo(const COptionModule *pOption,GameInfoT& info){
	/** GameInfo包括视觉信息和裁判信息，之后要加上方差等信息,player的信息全部加载进来，用于robot predictor **/
    static int last_cycle = 0;
    bool receive_new_vision = false;
    receive_vision_mutex.lock();
    if (visionInfo.cycle > last_cycle) {
        info = visionInfo;
        last_cycle = visionInfo.cycle;
        receive_new_vision = true;
    }
    receive_vision_mutex.unlock();
    return receive_new_vision;
}

void CDataReceiver4rbk::receiveRefMsgs() {
    Referee ssl_referee;
    QByteArray datagram;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (referee_socket.state() == QUdpSocket::BoundState && referee_socket.hasPendingDatagrams()) {
            //qDebug()<<"reveive_____________";
            datagram.resize(referee_socket.pendingDatagramSize());
            referee_socket.readDatagram(datagram.data(), datagram.size());
            ssl_referee.ParseFromArray((void*)datagram.data(), datagram.size());
            //update refereemsg
            unsigned long long packet_timestamp = ssl_referee.packet_timestamp();
            Referee_Stage stage = ssl_referee.stage();
            Referee_Command command = ssl_referee.command();
            unsigned long command_counter = ssl_referee.command_counter();
            unsigned long long command_timestamp = ssl_referee.command_timestamp();
            Referee_TeamInfo yellow = ssl_referee.yellow();
            Referee_TeamInfo blue = ssl_referee.blue();
            long long stage_time_left = 0;
            stage_time_left = ssl_referee.stage_time_left();
            char cmd;
            struct stGamePacket pCmd_temp;
            unsigned char cmd_index = 0;
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
            referee_mutex.lock();
            // Get Ball Placement Position
            if (command == 16 || command == 17) {
                refereeInfo.refMsg.ballPlacement.x = msgX2InfoX(ssl_referee.designated_position().x());
                refereeInfo.refMsg.ballPlacement.y = msgY2InfoY(ssl_referee.designated_position().y());
                //std::cout << "Received ball placement pos : " << msg.ballPlacementX << " ,  " << msg.ballPlacementY << std::endl;
            }

            pCmd_temp.cmd = cmd;
            pCmd_temp.cmd_counter = command_counter;
            pCmd_temp.goals_blue = blue.score();
            pCmd_temp.goals_yellow = yellow.score();
            pCmd_temp.time_remaining = stage_time_left / 1000000;
            static unsigned char former_cmd_index = 0;
            cmd_index = pCmd_temp.cmd_counter;
            if (cmd_index != former_cmd_index) {
                former_cmd_index = cmd_index;	// ������һ��ָ��ñ�־ֵ
                m_play_mode = PMNone;
                for( int pm = PMStop; pm <= PMNone; ++pm ) {
                    if( playModePair[pm].ch == cmd ) {
                        // Ѱ��ƥ���ָ������
                        m_play_mode = playModePair[pm].mode;
                        break;
                    }
                }
                if( m_play_mode != PMNone ) {
                    refereeInfo.mode = m_play_mode;
                    refereeInfo.refMsg.blueGoal = (int)pCmd_temp.goals_blue;
                    refereeInfo.refMsg.yellowGoal = (int)pCmd_temp.goals_yellow;
                    refereeInfo.refMsg.blueGoalie = (int)blue.goalkeeper();
                    refereeInfo.refMsg.yellowGoalie = (int)yellow.goalkeeper();
                    refereeInfo.refMsg.timeRemain = pCmd_temp.time_remaining;
                    std::cout << "Protobuf Protocol: RefereeBox Command : " << cmd << " what : " << playModePair[m_play_mode].what << std::endl;
                    //std::cout << "Stage_time_left : "<< msg.timeRemain << " Goals for blue : "<< (int)(pCmd_temp.goals_blue)
                    //	<< " Goals for yellow : "<< (int)(pCmd_temp.goals_yellow) << std::endl;
                }
            }
            referee_mutex.unlock();
        }
    }
}

bool CDataReceiver4rbk::getNewRefMsgs(GameInfoT& info){
    referee_mutex.lock();
    info.mode = refereeInfo.mode;
    info.refMsg = refereeInfo.refMsg;
    referee_mutex.unlock();
    return true;
}

bool CDataReceiver4rbk::getGameInfo(const COptionModule *pOption,GameInfoT& info){

    //get rawvision into visualinfo
	if (!rawVision2VisualInfo(pOption,info)){
		return false;
    }
    getNewRefMsgs(info);

	return true;
}
