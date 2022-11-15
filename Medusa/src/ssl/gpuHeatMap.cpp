#include "gpuHeatMap.h"
#include <robokit/core/logger.h>
#include <robokit/core/rbk_config.h>
#include <iostream>
#include "time.h"

using namespace std;

CGpuHeatMap::CGpuHeatMap()
{
    rbk::Config::Instance()->get("simOppo", is_change_port);
    if (is_change_port)
    {
        heat_port = 20004;
        heat_bind_port = 20009;
    }
    else
    {
        heat_port = 20003;
        heat_bind_port = 20008;
    }
    //heat_socket.bind(heat_bind_port);

    udpServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (udpServer == INVALID_SOCKET)LogInfo("udpServer is an invalid_socket");
    HeatAddr.sin_family = AF_INET;
    HeatAddr.sin_port = htons(heat_port);
    HeatAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
}

CGpuHeatMap::~CGpuHeatMap()
{
    closesocket(udpServer);
}

void CGpuHeatMap::run() {
    static int count = 0;
    boost::chrono::time_point<boost::chrono::steady_clock> tp1;
    boost::chrono::time_point<boost::chrono::steady_clock> tp2;
    tp1 = boost::chrono::steady_clock::now();
    while (true) {
        //msgs = new Heat_Map;
        setHeatPoints();
        //send();
        tp2 = boost::chrono::steady_clock::now();
        auto delt_time = boost::chrono::duration_cast<boost::chrono::milliseconds>((tp2 - tp1)).count();
        tp1 = tp2;
        //LogInfo(delt_time);
        if (delt_time < 1000.0 / 75) {
            Sleep(1000.0 / 75 - delt_time);
        }
    }
}

void CGpuHeatMap::setHeatPoints() 
{
    //将点均分为若干个颜色,现在情况为把所有点按分值大小分配为256部分，每部分对应一个颜色
    auto temp_points = temp_msgs.add_points();
    for (int i = 0; i < 1200; i+=10) {
        for (int j = 0; j < 900; j+=10) {        
            auto pos = temp_points->add_pos();
            pos->set_x(600 - i);
            pos->set_y(450 - j);
        }
    }
    //std::cout << Color_Range << std::endl;

    int color_size = temp_points->pos_size();
    for (int m = 0; m < 256; m++) {
        auto points = msgs.add_points(); //msgs->add_points();
        for (int n = m * color_size / 256; n < (m + 1) * color_size / 256; n++) {
            points->set_color(m);
            auto pos = points->add_pos();
            pos->set_x(temp_points->pos(n).x());
            pos->set_y(temp_points->pos(n).y());
            //pos->set_x(temp_points->pos(n).x());
            //pos->set_y(temp_points->pos(n).y());
            //score = scores.add_scores();
            //score->set_color(m);
            //p = score->add_p();
            //p->set_x(rawScores.at(n).x);
            //p->set_y(rawScores.at(n).y);
        }
        //由于UDP发包大小的限制，所以将颜色信息分批次发送
        if ((m + 1) % 8 == 0) {
            send();
        }
    }
    temp_msgs.Clear();
}

void CGpuHeatMap::send()
{
    //发送message//
    int size = msgs.ByteSize(); //msgs->ByteSize();
    char* output = new char[size];
    msgs.SerializeToArray(output, size); //msgs->SerializeToArray(output, size);
    //heat_socket.writeTo(output, size, "127.0.0.1", heat_port);
    sendto(udpServer, output, size, 0, (sockaddr*)&HeatAddr, sizeof(HeatAddr));

    //删除掉message的部分，回收空间//
    msgs.Clear(); //msgs->Clear();
    //delete[] msgs;
}
