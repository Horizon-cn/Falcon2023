#include "GDebugEngine.h"
#include <param.h>
#include <cstring>
#include <WorldModel/WorldModel.h>
#include <WorldModel/server.h>
#include "zss_debug.pb.h"
#include "staticparams.h"
#include <QMutex>

extern ZSS::Protocol::Debug_Msgs guiDebugMsgs;
extern QMutex* _debug_mutex;
CGDebugEngine::CGDebugEngine(){
}
CGDebugEngine::~CGDebugEngine(){
}

void CGDebugEngine::gui_debug_x(const CGeoPoint& p, char debug_color){
	CGeoPoint basePos = p;

	const CGeoPoint p1 = basePos + CVector(5, 5);
	const CGeoPoint p2 = basePos + CVector(-5,-5);
	gui_debug_line(p1, p2, debug_color);

	const CGeoPoint p3 = basePos + CVector(5,-5);
	const CGeoPoint p4 = basePos + CVector(-5, 5);
	gui_debug_line(p3,p4, debug_color);
}
void CGDebugEngine::gui_debug_line(const CGeoPoint& p1, const CGeoPoint& p2, char debug_color){
	ZSS::Protocol::Debug_Msg* msg = guiDebugMsgs.add_msgs();
	msg->set_type(ZSS::Protocol::Debug_Msg::LINE);
	msg->set_color(ZSS::Protocol::Debug_Msg_Color(debug_color));
	ZSS::Protocol::Debug_Line* line = msg->mutable_line();
	ZSS::Protocol::Point
		*pos1 = line->mutable_start(),
		*pos2 = line->mutable_end();
	if ( WorldModel::Instance()->option()->MySide() == Param::Field::POS_SIDE_RIGHT ){
		pos1->set_x(-p1.x());
		pos1->set_y(-p1.y());
		pos2->set_x(-p2.x());
		pos2->set_y(-p2.y());
	}else{
		pos1->set_x(p1.x());
		pos1->set_y(p1.y());
		pos2->set_x(p2.x());
		pos2->set_y(p2.y());
	}
	line->set_back(false);
	line->set_forward(true);
	//net_gdebug the_debug = {NET_GUI_DEBUG_LINE, 0, 0, debug_color, 1};
	//the_debug.info.line.p[0] = pos1;
	//the_debug.info.line.p[1] = pos2;
	//the_debug.info.line.flags = 0;
	//gui_debug_add(the_debug);
}
void CGDebugEngine::gui_debug_arc(const CGeoPoint& p, double r, double start_angle, double span_angle, char debug_color){
	ZSS::Protocol::Debug_Msg* msg = guiDebugMsgs.add_msgs();
	msg->set_type(ZSS::Protocol::Debug_Msg::ARC);
	msg->set_color(ZSS::Protocol::Debug_Msg_Color(debug_color));
	ZSS::Protocol::Debug_Arc* arc = msg->mutable_arc();
	arc->set_start(start_angle);
	arc->set_end(span_angle);
	arc->set_fill(false);
	ZSS::Protocol::Rectangle* rec = arc->mutable_rectangle();
	ZSS::Protocol::Point
		*p1 = rec->mutable_point1(),
		*p2 = rec->mutable_point2();
	PosT center;
	if ( WorldModel::Instance()->option()->MySide() == Param::Field::POS_SIDE_RIGHT ){
		center.x = -p.x();
		center.y = -p.y();
	}
	else{
		center.x = p.x();
		center.y = p.y();
	}
	p1->set_x(center.x - r);
	p1->set_y(center.y - r);
	p2->set_x(center.x + r);
	p2->set_y(center.y + r);
	//net_gdebug the_debug = {NET_GUI_DEBUG_ARC, 0, 0, debug_color, 1};
	//the_debug.info.arc.center = center;
	//the_debug.info.arc.r = r;
	//the_debug.info.arc.a1 = start_angle;
	//the_debug.info.arc.a2 = span_angle;
	//the_debug.info.arc.flags = 0;

	//gui_debug_add(the_debug);
}
void CGDebugEngine::gui_debug_triangle(const CGeoPoint& p1, const CGeoPoint& p2, const CGeoPoint& p3, char debug_color){
	ZSS::Protocol::Debug_Msg* msg = guiDebugMsgs.add_msgs();
	msg->set_type(ZSS::Protocol::Debug_Msg::POLYGON);
	msg->set_color(ZSS::Protocol::Debug_Msg_Color(debug_color));
	ZSS::Protocol::Debug_Polygon* tri = msg->mutable_polygon();
	ZSS::Protocol::Point* pos1 = tri->add_vertex();
	ZSS::Protocol::Point* pos2 = tri->add_vertex();
	ZSS::Protocol::Point* pos3 = tri->add_vertex();
	if ( WorldModel::Instance()->option()->MySide() == Param::Field::POS_SIDE_RIGHT ){
		pos1->set_x(-p1.x());
		pos1->set_y(-p1.y());
		pos2->set_x(-p2.x());
		pos2->set_y(-p2.y());
		pos3->set_x(-p3.x());
		pos3->set_y(-p3.y());
	}
	else{
		pos1->set_x(p1.x());
		pos1->set_y(p1.y());
		pos2->set_x(p2.x());
		pos2->set_y(p2.y());
		pos3->set_x(p3.x());
		pos3->set_y(p3.y());
	}
	tri->set_fill(true);
	//net_gdebug the_debug = {NET_GUI_DEBUG_TRIANGLE, 0, 0, debug_color, 1};
	//the_debug.info.tri.p[0] = pos1;
	//the_debug.info.tri.p[1] = pos2;
	//the_debug.info.tri.p[2]	= pos3;

	//gui_debug_add(the_debug);
}
void CGDebugEngine::gui_debug_robot(const CGeoPoint& p, double robot_dir){
	ZSS::Protocol::Debug_Msg* msg = guiDebugMsgs.add_msgs();
	msg->set_type(ZSS::Protocol::Debug_Msg::ROBOT);
	msg->set_color(ZSS::Protocol::Debug_Msg_Color(0));
	ZSS::Protocol::Debug_Robot* robot = msg->mutable_robot();

	float rdir;
	if ( WorldModel::Instance()->option()->MySide() == Param::Field::POS_SIDE_RIGHT ){
		robot_dir = Utils::Normalize(robot_dir + Param::Math::PI);
	}
	rdir = robot_dir*180/Param::Math::PI; // ×ª³É½Ç¶È
	robot->set_dir(rdir);

	ZSS::Protocol::Point* robot_pos = robot->mutable_pos();

	if ( WorldModel::Instance()->option()->MySide() == Param::Field::POS_SIDE_RIGHT ){
		robot_pos->set_x(-p.x());
		robot_pos->set_y(-p.y());
	}
	else{
		robot_pos->set_x(p.x());
		robot_pos->set_y(p.y());
	}
	
	//net_gdebug the_debug = {NET_GUI_DEBUG_ROBOT, 0, 0, 0, 1};
	//the_debug.info.car.p = robot_pos;
	//the_debug.info.car.dir = rdir;

	//gui_debug_add(the_debug);
}
void CGDebugEngine::gui_debug_msg(const CGeoPoint& p, const char* msgstr, char debug_color)
{
	ZSS::Protocol::Debug_Msg* msg = guiDebugMsgs.add_msgs();
	msg->set_type(ZSS::Protocol::Debug_Msg::TEXT);
	msg->set_color(ZSS::Protocol::Debug_Msg_Color(debug_color));
	ZSS::Protocol::Debug_Text* text = msg->mutable_text();
	ZSS::Protocol::Point* center = text->mutable_pos();
	if ( WorldModel::Instance()->option()->MySide() == Param::Field::POS_SIDE_RIGHT ){
		center->set_x(-p.x());
		center->set_y(-p.y());
	}
	else{
		center->set_x(p.x());
		center->set_y(p.y());
	}
	text->set_text(msgstr);
	//net_gdebug the_debug = {NET_GUI_DEBUG_FIELD_MSG, 0, 0, debug_color, 1};
	//strcpy(the_debug.info.msg.msg, msgstr);
	//the_debug.info.msg.p = center;

	//gui_debug_add(the_debug);
}
void CGDebugEngine::gui_debug_curve(const double num, const double maxLimit, const double minLimit, char debug_color)
{
	ZSS::Protocol::Debug_Msg* msg = guiDebugMsgs.add_msgs();
	msg->set_type(ZSS::Protocol::Debug_Msg::CURVE);
	msg->set_color(ZSS::Protocol::Debug_Msg_Color(debug_color));
	ZSS::Protocol::Debug_Curve_* curve = msg->mutable_curve();
	curve->set_num(num);
	curve->set_minlimit(minLimit);
	curve->set_maxlimit(maxLimit);
}
void CGDebugEngine::gui_debug_add(const net_gdebug& new_debug)
{
	//_debugs.push(new_debug);
}

void CGDebugEngine::send(bool teamIsBlue){
    static QByteArray data;
    _debug_mutex->lock();
    int size = guiDebugMsgs.ByteSize();
    data.resize(size);
    guiDebugMsgs.SerializeToArray(data.data(),size);
    int sent_size = 0;
    if(teamIsBlue){
        sent_size = debug_socket.writeDatagram(data,data.size(),QHostAddress(ZSS::LOCAL_ADDRESS),ZSS::Medusa::DEBUG_MSG_SEND[Param::BLUE]);
    } else {
        sent_size = debug_socket.writeDatagram(data,data.size(),QHostAddress(ZSS::LOCAL_ADDRESS),ZSS::Medusa::DEBUG_MSG_SEND[Param::YELLOW]);
    }
//    std::cout << "size: " << data.size() << ' ' << sent_size << std::endl;
    guiDebugMsgs.clear_msgs();
    _debug_mutex->unlock();
}
