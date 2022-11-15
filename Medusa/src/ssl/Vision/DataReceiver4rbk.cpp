#include "DataReceiver4rbk.h"
#include "SSLStrategy.h"
#include "referee.pb.h"
#include "src_rawvision.pb.h"
#include "utils.h"
#include "OptionModule.h"
#include "game_state.h"
#include <tinyxml/ParamReader.h>

namespace {
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
	float msgAngle2InfoAngle(float angle) { return -Utils::Deg2Rad(angle); }
}
CDataReceiver4rbk::CDataReceiver4rbk() {
	m_play_mode = PMNone;
}

CDataReceiver4rbk::~CDataReceiver4rbk(void) {
}
bool CDataReceiver4rbk::rawVision2VisualInfo(const COptionModule *pOption,GameInfoT& info){
	/** GameInfo包括视觉信息和裁判信息，之后要加上方差等信息,player的信息全部加载进来，用于robot predictor **/
	//pOption->update();
	static int strategy_cycle = 0;
	rbk::protocol::SRC_RawVision vision;
	GRBKHandle::Instance()->getSubscriberData(vision);
	info.cycle = ++strategy_cycle;
	info.mode = m_play_mode;
	info.ball.pos.valid = vision.ball().ball_found();
	info.ball.pos.x = msgX2InfoX(vision.ball().x());
	info.ball.pos.y = msgY2InfoY(vision.ball().y());
	//LogInfo("pinfo->ball.x   "<<info.ball.pos.x<<" validity  "<< info.ball.pos.valid);
	info.ball.vel = CVector(msgX2InfoX(vision.ball().vel_x()), msgY2InfoY(vision.ball().vel_y()));
	info.ball.chipPredict.x = msgX2InfoX(vision.ball().chip_predict_x());
	info.ball.chipPredict.y = msgY2InfoY(vision.ball().chip_predict_y());
	//info.ball_P.from_string(vision.ball().p());
	//info.ball_Q.from_string(vision.ball().q());
	for (int i = 0; i < Param::Field::MAX_PLAYER * 2; i++) {
		info.player[i].dir = 0;
		info.player[i].pos.valid = 0;
		info.player[i].ID = -1;
		info.player[i].isYellow = true;
		info.player[i].pos.x = 9999;
		info.player[i].pos.y = 9999;
		info.player[i].vel = CVector(0, 0);
		info.player[i].acc = CVector(0, 0);
		//info.player[i].P.from_string(robot.p());
		//info.player[i].Q.from_string(robot.q());
	}
	if (pOption->MyColor() == TEAM_BLUE){
		for(int i=0;i<vision.robots_blue_size();i++){
			const rbk::protocol::Robot& robot = vision.robots_blue(i);
			info.player[i].dir = msgAngle2InfoAngle(robot.orientation());
			info.player[i].pos.valid = robot.robot_found();
			info.player[i].ID = robot.robot_id();
			info.player[i].isYellow = false;
			info.player[i].pos.x = msgX2InfoX(robot.x());
			info.player[i].pos.y = msgY2InfoY(robot.y());
			info.player[i].vel = CVector(msgX2InfoX(robot.vel_x()), msgY2InfoY(robot.vel_y()));
			info.player[i].acc = CVector(msgX2InfoX(robot.accelerate_x()), msgY2InfoY(robot.accelerate_y()));
			//info.player[i].P.from_string(robot.p());
			//info.player[i].Q.from_string(robot.q());
		}
		for(int i=Param::Field::MAX_PLAYER;i<Param::Field::MAX_PLAYER+vision.robots_yellow_size();i++){
			const rbk::protocol::Robot& robot = vision.robots_yellow(i-Param::Field::MAX_PLAYER);
			info.player[i].dir = msgAngle2InfoAngle(robot.orientation());
			info.player[i].pos.valid = robot.robot_found();
			info.player[i].ID = robot.robot_id();
			info.player[i].isYellow = true;
			info.player[i].pos.x = msgX2InfoX(robot.x());
			info.player[i].pos.y = msgY2InfoY(robot.y());
			info.player[i].vel = CVector(msgX2InfoX(robot.vel_x()), msgY2InfoY(robot.vel_y()));
			info.player[i].acc = CVector(msgX2InfoX(robot.accelerate_x()), msgY2InfoY(robot.accelerate_y()));
			//info.player[i].P.from_string(robot.p());
			//info.player[i].Q.from_string(robot.q());
		}
	}else{
		for(int i=0;i<vision.robots_yellow_size();i++){
			const rbk::protocol::Robot& robot = vision.robots_yellow(i);
			info.player[i].dir = msgAngle2InfoAngle(robot.orientation());
			info.player[i].pos.valid = robot.robot_found();
			info.player[i].ID = robot.robot_id();
			info.player[i].isYellow = true;
			info.player[i].pos.x = msgX2InfoX(robot.x());
			info.player[i].pos.y = msgY2InfoY(robot.y());
			info.player[i].vel = CVector(msgX2InfoX(robot.vel_x()), msgY2InfoY(robot.vel_y()));
			info.player[i].acc = CVector(msgX2InfoX(robot.accelerate_x()), msgY2InfoY(robot.accelerate_y()));
			//info.player[i].P.from_string(robot.p());
			//info.player[i].Q.from_string(robot.q());
		}
		for(int i=Param::Field::MAX_PLAYER;i<Param::Field::MAX_PLAYER+vision.robots_blue_size();i++){
			const rbk::protocol::Robot& robot = vision.robots_blue(i-Param::Field::MAX_PLAYER);
			info.player[i].dir = msgAngle2InfoAngle(robot.orientation());
			info.player[i].pos.valid = robot.robot_found();
			info.player[i].ID = robot.robot_id();
			info.player[i].isYellow = false;
			info.player[i].pos.x = msgX2InfoX(robot.x());
			info.player[i].pos.y = msgY2InfoY(robot.y());
			info.player[i].vel = CVector(msgX2InfoX(robot.vel_x()), msgY2InfoY(robot.vel_y()));
			info.player[i].acc = CVector(msgX2InfoX(robot.accelerate_x()), msgY2InfoY(robot.accelerate_y()));
			//info.player[i].P.from_string(robot.p());
			//info.player[i].Q.from_string(robot.q());
		}
	}
	//debug
	//for (int i = 0; i < 6 * 2; i++) {
	//	LogInfo("index: "<<i);
	//	LogInfo(info.player[i].pos.valid);
	//	LogInfo(info.player[i].ID);
	//	LogInfo(info.player[i].isYellow);
	//	LogInfo(info.player[i].pos.x);
	//	LogInfo(info.player[i].pos.y);
	//}
	return true;
}

bool CDataReceiver4rbk::getGameInfo(const COptionModule *pOption,GameInfoT& info){
	SSL_Referee ssl_referee;
	GRBKHandle::Instance()->getSubscriberData(ssl_referee);

	//get rawvision into visualinfo
	if (!rawVision2VisualInfo(pOption,info)){
		return false;
	}

	//update refereemsg
	unsigned long long packet_timestamp = ssl_referee.packet_timestamp();
	SSL_Referee_Stage stage = ssl_referee.stage();
	SSL_Referee_Command command = ssl_referee.command();
	unsigned long command_counter = ssl_referee.command_counter();
	unsigned long long command_timestamp = ssl_referee.command_timestamp();
	SSL_Referee_TeamInfo yellow = ssl_referee.yellow();
	SSL_Referee_TeamInfo blue = ssl_referee.blue();
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
	// Get Ball Placement Position
	if (command == 16 || command == 17) {
		info.refMsg.ballPlacement.x = msgX2InfoX(ssl_referee.designated_position().x());
		info.refMsg.ballPlacement.y = msgY2InfoY(ssl_referee.designated_position().y());
		//std::cout << "Received ball placement pos : " << msg.ballPlacementX << " ,  " << msg.ballPlacementY << std::endl;
	}

	pCmd_temp.cmd = cmd;
	pCmd_temp.cmd_counter = command_counter; 
	pCmd_temp.goals_blue = blue.score();
	pCmd_temp.goals_yellow = yellow.score();
	pCmd_temp.time_remaining = unsigned short(stage_time_left / 1000000);
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
			info.mode = m_play_mode;
			info.refMsg.blueGoal = (int)pCmd_temp.goals_blue;
			info.refMsg.yellowGoal = (int)pCmd_temp.goals_yellow;
			info.refMsg.blueGoalie = (int)blue.goalie();
			info.refMsg.yellowGoalie = (int)yellow.goalie();
			info.refMsg.timeRemain = pCmd_temp.time_remaining;
			std::cout << "Protobuf Protocol: RefereeBox Command : " << cmd << " what : " << playModePair[m_play_mode].what << std::endl;
			//std::cout << "Stage_time_left : "<< msg.timeRemain << " Goals for blue : "<< (int)(pCmd_temp.goals_blue)
			//	<< " Goals for yellow : "<< (int)(pCmd_temp.goals_yellow) << std::endl;
		}
	}
	return true;
}