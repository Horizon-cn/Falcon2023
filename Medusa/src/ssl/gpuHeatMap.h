#ifndef CGPUHEATMAP_H
#define CGPUHEATMAP_H

#include <singleton.h>
#include <robokit/core/rbk_core.h>
#include <robokit/utils/udp/udp_client.h>
#include "src_heatMap.pb.h"

using namespace rbk;

class CGpuHeatMap 
{
public:
    CGpuHeatMap();
    virtual ~CGpuHeatMap();
    void run();
	
private:
    const int Color_Range = 256;

    void send();
    void setHeatPoints();

    SOCKET udpServer;
    SOCKADDR_IN HeatAddr;
    rbk::utils::udp::SyncUDPClient heat_socket;
    bool is_change_port;
    int heat_port, heat_bind_port;
    //Heat_Map* msgs;
    Heat_Map temp_msgs;
    Heat_Map msgs;

    float* map_cpu, * start_pos_cpu;
};
typedef NormalSingleton< CGpuHeatMap > gpuHeatMap;

#endif
