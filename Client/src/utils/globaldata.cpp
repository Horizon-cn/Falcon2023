#include "globaldata.h"
#include "parammanager.h"
#include "staticparams.h"
#include "globalsettings.h"
namespace  {
    auto GS = GlobalSettings::Instance();
    auto vpm = Owl::VParamManager::Instance();
    auto opm = Owl::OParamManager::Instance();
}
CGlobalData::CGlobalData(): ctrlC(false)
    , refereeMode(0)
    , maintain(Vision::MAINTAIN_STORE_BUFFER)
    , processBall(Vision::BALL_STORE_BUFFER)
    , processRobot(Vision::ROBOT_STORE_BUFFER)
    , ballrecords(Vision::BALL_STORE_BUFFER) {
    std::fill_n(cameraControl, PARAM::CAMERA, false);
    std::fill_n(processControl, PARAM::PROCESS, false);
    for(int i = 0; i < PARAM::CAMERA; i++) {
        cameraMatrix[i].id = i;
    }
    for(int i = 0; i < opm->total_cameras; i++) {
        cameraControl[i] = true;
    }
    initVision();
}

void CGlobalData::initVision() {
    setCameraMatrix();
    std::fill_n(cameraUpdate, PARAM::CAMERA, false);
    maintain.clear();
    processBall.clear();
    processRobot.clear();
    ballrecords.clear();
    lastTouch = -1;
    updateSimVision = false;
    for (int i = 0; i < PARAM::CAMERA; i++) {
        camera[i].clear();
    }
    for(int t = PARAM::BLUE; t < PARAM::TEAMS; t++) {
        for(int i = 0; i < PARAM::ROBOTMAXID; i++) {
            robotPossible[t][i] = 0;
            robotInformation[t][i].fill(false,false,false,0,0);
        }
    }
    for(int t = PARAM::BLUE; t < PARAM::TEAMS; t++) {
        robotCommand[t] = DataQueue<Owl::RobotCommands>(Vision::COMMAND_STORE_BUFFER);
        commandMissingFrame[t] = 0;
    }
}

void CGlobalData::setCameraMatrix() {
    if (opm->field == "Division_A" && (opm->saoAction == 0 || opm->saoAction == 4))
        setCameraMatrixA();
    else
        setCameraMatrixB();
    /**
    for (int i = 0; i < PARAM::CAMERA; i++) {
        double x, y;
        vpm->loadParam(x, "Camera" + QString::number(i) + "CenterX", 0);
        vpm->loadParam(y, "Camera" + QString::number(i) + "CenterY", 0);
        cameraMatrix[i].fillCenter(saoConvert(CGeoPoint(x, y)));
    }
    for (int i = 0; i < PARAM::CAMERA; i++) {
        vpm->loadParam(cameraMatrix[i].leftedge.min,    "Camera" + QString::number(i) + "Leftmin",  cameraMatrix[i].campos.x());
        vpm->loadParam(cameraMatrix[i].leftedge.max,    "Camera" + QString::number(i) + "Leftmax",  cameraMatrix[i].campos.x());
        vpm->loadParam(cameraMatrix[i].rightedge.min,   "Camera" + QString::number(i) + "Rightmin", cameraMatrix[i].campos.x());
        vpm->loadParam(cameraMatrix[i].rightedge.max,   "Camera" + QString::number(i) + "Rightmax", cameraMatrix[i].campos.x());
        vpm->loadParam(cameraMatrix[i].upedge.min,      "Camera" + QString::number(i) + "Upmin",    cameraMatrix[i].campos.y());
        vpm->loadParam(cameraMatrix[i].upedge.max,      "Camera" + QString::number(i) + "Upmax",    cameraMatrix[i].campos.y());
        vpm->loadParam(cameraMatrix[i].downedge.min,    "Camera" + QString::number(i) + "Downmin",  cameraMatrix[i].campos.y());
        vpm->loadParam(cameraMatrix[i].downedge.max,    "Camera" + QString::number(i) + "Downmax",  cameraMatrix[i].campos.y());
    }
    **/
    saoConvertEdge();
}
// edge.min组成相机最大范围，edge.max定义最精确范围
void CGlobalData::setCameraMatrixA() {
    switch(opm->total_cameras) {
        case 1:
            cameraMatrix[0].fillCenter(GS->saoConvert(CGeoPoint(0, 0)));
            cameraMatrix[0].height = 6000;
            cameraMatrix[0].leftedge.min = cameraMatrix[0].campos.x() - 6534;
            cameraMatrix[0].leftedge.max = cameraMatrix[0].campos.x() - 6000;
            cameraMatrix[0].rightedge.min = cameraMatrix[0].campos.x() + 6534;
            cameraMatrix[0].rightedge.max = cameraMatrix[0].campos.x() + 6000;
            cameraMatrix[0].downedge.min = cameraMatrix[0].campos.y() - 5100;
            cameraMatrix[0].downedge.max = cameraMatrix[0].campos.y() - 4500;
            cameraMatrix[0].upedge.min = cameraMatrix[0].campos.y() + 5100;
            cameraMatrix[0].upedge.max = cameraMatrix[0].campos.y() + 4500;
            break;
        case 2:
            cameraMatrix[0].fillCenter(GS->saoConvert(CGeoPoint(-3170, 0)));
            cameraMatrix[1].fillCenter(GS->saoConvert(CGeoPoint(3000, 0)));
            for (int i = 0; i < opm->total_cameras; i = i + 1) {
                cameraMatrix[i].height = 6000;
                cameraMatrix[i].leftedge.min = cameraMatrix[i].campos.x() - 3400;
                cameraMatrix[i].leftedge.max = cameraMatrix[i].campos.x() - 2800;
                cameraMatrix[i].rightedge.min = cameraMatrix[i].campos.x() + 3400;
                cameraMatrix[i].rightedge.max = cameraMatrix[i].campos.x() + 2800;
                cameraMatrix[i].downedge.min = cameraMatrix[i].campos.y() - 4800;
                cameraMatrix[i].downedge.max = cameraMatrix[i].campos.y() - 4800;
                cameraMatrix[i].upedge.min = cameraMatrix[i].campos.y() + 4900;
                cameraMatrix[i].upedge.max = cameraMatrix[i].campos.y() + 4900;
            }
            break;
        case 4:
            cameraMatrix[0].fillCenter(GS->saoConvert(CGeoPoint(-3000, -2250)));
            cameraMatrix[1].fillCenter(GS->saoConvert(CGeoPoint(-3000, 2250)));
            cameraMatrix[2].fillCenter(GS->saoConvert(CGeoPoint(3000, -2250)));
            cameraMatrix[3].fillCenter(GS->saoConvert(CGeoPoint(3000, 2250)));
            for (int i = 0; i < opm->total_cameras; i++) {
                cameraMatrix[i].height = 6000;
                cameraMatrix[i].leftedge.min = cameraMatrix[i].campos.x() - 4400;
                cameraMatrix[i].leftedge.max = cameraMatrix[i].campos.x() - 4000;
                cameraMatrix[i].rightedge.min = cameraMatrix[i].campos.x() + 4400;
                cameraMatrix[i].rightedge.max = cameraMatrix[i].campos.x() + 4000;
                cameraMatrix[i].downedge.min = cameraMatrix[i].campos.y() - 3825;
                cameraMatrix[i].downedge.max = cameraMatrix[i].campos.y() - 3375;
                cameraMatrix[i].upedge.min = cameraMatrix[i].campos.y() + 3825;
                cameraMatrix[i].upedge.max = cameraMatrix[i].campos.y() + 3375;
            }
            break;
        case 8:
            cameraMatrix[0].fillCenter(GS->saoConvert(CGeoPoint(-4500, -2250)));
            cameraMatrix[1].fillCenter(GS->saoConvert(CGeoPoint(-4500, 2250)));
            cameraMatrix[2].fillCenter(GS->saoConvert(CGeoPoint(-1500, -2250)));
            cameraMatrix[3].fillCenter(GS->saoConvert(CGeoPoint(-1500, 2250)));
            cameraMatrix[4].fillCenter(GS->saoConvert(CGeoPoint(1500, -2250)));
            cameraMatrix[5].fillCenter(GS->saoConvert(CGeoPoint(1500, 2250)));
            cameraMatrix[6].fillCenter(GS->saoConvert(CGeoPoint(4500, -2250)));
            cameraMatrix[7].fillCenter(GS->saoConvert(CGeoPoint(4500, 2250)));
            for (int i = 0; i < opm->total_cameras; i++) {
                cameraMatrix[i].height = 6000;
                cameraMatrix[i].leftedge.min = cameraMatrix[i].campos.x() - 2550;
                cameraMatrix[i].leftedge.max = cameraMatrix[i].campos.x() - 2250;
                cameraMatrix[i].rightedge.min = cameraMatrix[i].campos.x() + 2550;
                cameraMatrix[i].rightedge.max = cameraMatrix[i].campos.x() + 2250;
                cameraMatrix[i].downedge.min = cameraMatrix[i].campos.y() - 3300;
                cameraMatrix[i].downedge.max = cameraMatrix[i].campos.y() - 3000;
                cameraMatrix[i].upedge.min = cameraMatrix[i].campos.y() + 3300;
                cameraMatrix[i].upedge.max = cameraMatrix[i].campos.y() + 3000;
            }
            break;   
        default:
            break;
    }
}

void CGlobalData::setCameraMatrixB() {
    switch(opm->total_cameras) {
        case 1:
            cameraMatrix[0].fillCenter(GS->saoConvert(CGeoPoint(0, 0)));
            cameraMatrix[0].height = 4000;
            cameraMatrix[0].leftedge.min = cameraMatrix[0].campos.x() - 4900;
            cameraMatrix[0].leftedge.max = cameraMatrix[0].campos.x() - 4500;
            cameraMatrix[0].rightedge.min = cameraMatrix[0].campos.x() + 4900;
            cameraMatrix[0].rightedge.max = cameraMatrix[0].campos.x() + 4500;
            cameraMatrix[0].downedge.min = cameraMatrix[0].campos.y() - 3400;
            cameraMatrix[0].downedge.max = cameraMatrix[0].campos.y() - 3000;
            cameraMatrix[0].upedge.min = cameraMatrix[0].campos.y() + 3400;
            cameraMatrix[0].upedge.max = cameraMatrix[0].campos.y() + 3000;
            break;
        case 2:
            cameraMatrix[0].fillCenter(GS->saoConvert(CGeoPoint(-2250, 0)));
            cameraMatrix[1].fillCenter(GS->saoConvert(CGeoPoint(2250, 0)));
            for (int i = 0; i < opm->total_cameras; i = i + 1) {
                cameraMatrix[i].height = 4000;
                cameraMatrix[i].leftedge.min = cameraMatrix[i].campos.x() - 2350;
                cameraMatrix[i].leftedge.max = cameraMatrix[i].campos.x() - 2250;
                cameraMatrix[i].rightedge.min = cameraMatrix[i].campos.x() + 2350;
                cameraMatrix[i].rightedge.max = cameraMatrix[i].campos.x() + 2250;
                cameraMatrix[i].downedge.min = cameraMatrix[i].campos.y() - 3400;
                cameraMatrix[i].downedge.max = cameraMatrix[i].campos.y() - 3000;
                cameraMatrix[i].upedge.min = cameraMatrix[i].campos.y() + 3400;
                cameraMatrix[i].upedge.max = cameraMatrix[i].campos.y() + 3000;
            }
            break;
        case 4:
            cameraMatrix[0].fillCenter(GS->saoConvert(CGeoPoint(-2195, -1404)));
            cameraMatrix[1].fillCenter(GS->saoConvert(CGeoPoint(-2310, 1477)));
            cameraMatrix[2].fillCenter(GS->saoConvert(CGeoPoint(2162, -1529)));
            cameraMatrix[3].fillCenter(GS->saoConvert(CGeoPoint(2410, 1579)));          
            for (int i = 0; i < opm->total_cameras; i++) {
                cameraMatrix[i].height = 4000;
                cameraMatrix[i].leftedge.min = cameraMatrix[i].campos.x() - 3300;
                cameraMatrix[i].leftedge.max = cameraMatrix[i].campos.x() - 3000;
                cameraMatrix[i].rightedge.min = cameraMatrix[i].campos.x() + 3300;
                cameraMatrix[i].rightedge.max = cameraMatrix[i].campos.x() + 3000;
                cameraMatrix[i].downedge.min = cameraMatrix[i].campos.y() - 2550;
                cameraMatrix[i].downedge.max = cameraMatrix[i].campos.y() - 2250;
                cameraMatrix[i].upedge.min = cameraMatrix[i].campos.y() + 2550;
                cameraMatrix[i].upedge.max = cameraMatrix[i].campos.y() + 2250;
            }
            break;
        case 8:
            cameraMatrix[0].fillCenter(GS->saoConvert(CGeoPoint(-3375, -1500)));
            cameraMatrix[1].fillCenter(GS->saoConvert(CGeoPoint(-3375, 1500)));
            cameraMatrix[2].fillCenter(GS->saoConvert(CGeoPoint(-1125, -1500)));
            cameraMatrix[3].fillCenter(GS->saoConvert(CGeoPoint(-1125, 1500)));
            cameraMatrix[4].fillCenter(GS->saoConvert(CGeoPoint(1125, -1500)));
            cameraMatrix[5].fillCenter(GS->saoConvert(CGeoPoint(1125, 1500)));
            cameraMatrix[6].fillCenter(GS->saoConvert(CGeoPoint(3375, -1500)));
            cameraMatrix[7].fillCenter(GS->saoConvert(CGeoPoint(3375, 1500)));           
            for (int i = 0; i < opm->total_cameras; i++) {
                cameraMatrix[i].height = 4000;
                cameraMatrix[i].leftedge.min = cameraMatrix[i].campos.x() - 2350;
                cameraMatrix[i].leftedge.max = cameraMatrix[i].campos.x() - 2250;
                cameraMatrix[i].rightedge.min = cameraMatrix[i].campos.x() + 2350;
                cameraMatrix[i].rightedge.max = cameraMatrix[i].campos.x() + 2250;
                cameraMatrix[i].downedge.min = cameraMatrix[i].campos.y() - 3400;
                cameraMatrix[i].downedge.max = cameraMatrix[i].campos.y() - 3000;
                cameraMatrix[i].upedge.min = cameraMatrix[i].campos.y() + 3400;
                cameraMatrix[i].upedge.max = cameraMatrix[i].campos.y() + 3000;
            }
            break;
        default:
            break;
    }
}

void CGlobalData::saoConvertEdge() {
    switch (opm->saoAction) {
    case 0:
        for (int i = 0; i < opm->total_cameras; i++) {
            cameraMatrix[i].leftedge.min = cameraMatrix[i].leftedge.min;
            cameraMatrix[i].leftedge.max = cameraMatrix[i].leftedge.max;
            cameraMatrix[i].rightedge.min = cameraMatrix[i].rightedge.min;
            cameraMatrix[i].rightedge.max = cameraMatrix[i].rightedge.max;
            cameraMatrix[i].downedge.min = cameraMatrix[i].downedge.min;
            cameraMatrix[i].downedge.max = cameraMatrix[i].downedge.max;
            cameraMatrix[i].upedge.min = cameraMatrix[i].upedge.min;
            cameraMatrix[i].upedge.max = cameraMatrix[i].upedge.max;
        }
        break;
    case 1:
        for (int i = 0; i < opm->total_cameras; i++) {
            double transformEdge1 = cameraMatrix[i].campos.x() - cameraMatrix[i].campos.y();
            double transformEdge2 = cameraMatrix[i].campos.x() + cameraMatrix[i].campos.y();
            Owl::CameraEdge tempRightEdge = cameraMatrix[i].rightedge, tempLeftEdge = cameraMatrix[i].leftedge;
            cameraMatrix[i].leftedge.min = cameraMatrix[i].downedge.min + transformEdge1;
            cameraMatrix[i].leftedge.max = cameraMatrix[i].downedge.max + transformEdge1;
            cameraMatrix[i].rightedge.min = cameraMatrix[i].upedge.min + transformEdge1;
            cameraMatrix[i].rightedge.max = cameraMatrix[i].upedge.max + transformEdge1;
            cameraMatrix[i].downedge.min = -tempRightEdge.min + transformEdge2;
            cameraMatrix[i].downedge.max = -tempRightEdge.max + transformEdge2;
            cameraMatrix[i].upedge.min = -tempLeftEdge.min + transformEdge2;
            cameraMatrix[i].upedge.max = -tempLeftEdge.max + transformEdge2;
        }
        break;
    case 2:
        for (int i = 0; i < opm->total_cameras; i++) {
            double transformEdge1 = cameraMatrix[i].campos.x() - cameraMatrix[i].campos.y();
            double transformEdge2 = cameraMatrix[i].campos.x() + cameraMatrix[i].campos.y();
            Owl::CameraEdge tempRightEdge = cameraMatrix[i].rightedge, tempLeftEdge = cameraMatrix[i].leftedge;
            cameraMatrix[i].leftedge.min = -cameraMatrix[i].upedge.min + transformEdge2;
            cameraMatrix[i].leftedge.max = -cameraMatrix[i].upedge.max + transformEdge2;
            cameraMatrix[i].rightedge.min = -cameraMatrix[i].downedge.min + transformEdge2;
            cameraMatrix[i].rightedge.max = -cameraMatrix[i].downedge.max + transformEdge2;
            cameraMatrix[i].downedge.min = tempLeftEdge.min - transformEdge1;
            cameraMatrix[i].downedge.max = tempLeftEdge.max - transformEdge1;
            cameraMatrix[i].upedge.min = tempRightEdge.min - transformEdge1;
            cameraMatrix[i].upedge.max = tempRightEdge.max - transformEdge1;
        }
        break;
    case 3:
        for (int i = 0; i < opm->total_cameras; i++) {
            cameraMatrix[i].leftedge.min = (cameraMatrix[i].leftedge.min - cameraMatrix[i].campos.x()) * 4 / 3 + cameraMatrix[i].campos.x();
            cameraMatrix[i].leftedge.max = (cameraMatrix[i].leftedge.max - cameraMatrix[i].campos.x()) * 4 / 3 + cameraMatrix[i].campos.x();
            cameraMatrix[i].rightedge.min = (cameraMatrix[i].rightedge.min - cameraMatrix[i].campos.x()) * 4 / 3 + cameraMatrix[i].campos.x();
            cameraMatrix[i].rightedge.max = (cameraMatrix[i].rightedge.max - cameraMatrix[i].campos.x()) * 4 / 3 + cameraMatrix[i].campos.x();
            cameraMatrix[i].downedge.min = (cameraMatrix[i].downedge.min - cameraMatrix[i].campos.y()) * 3 / 2 + cameraMatrix[i].campos.y();
            cameraMatrix[i].downedge.max = (cameraMatrix[i].downedge.max - cameraMatrix[i].campos.y()) * 3 / 2 + cameraMatrix[i].campos.y();
            cameraMatrix[i].upedge.min = (cameraMatrix[i].upedge.min - cameraMatrix[i].campos.y()) * 3 / 2 + cameraMatrix[i].campos.y();
            cameraMatrix[i].upedge.max = (cameraMatrix[i].upedge.max - cameraMatrix[i].campos.y()) * 3 / 2 + cameraMatrix[i].campos.y();
        }
        break;
    case 4:
        for (int i = 0; i < opm->total_cameras; i++) {
            cameraMatrix[i].leftedge.min = cameraMatrix[i].leftedge.min;
            cameraMatrix[i].leftedge.max = cameraMatrix[i].leftedge.max;
            cameraMatrix[i].rightedge.min = cameraMatrix[i].rightedge.min;
            cameraMatrix[i].rightedge.max = cameraMatrix[i].rightedge.max;
            cameraMatrix[i].downedge.min = cameraMatrix[i].downedge.min;
            cameraMatrix[i].downedge.max = cameraMatrix[i].downedge.max;
            cameraMatrix[i].upedge.min = cameraMatrix[i].upedge.min;
            cameraMatrix[i].upedge.max = cameraMatrix[i].upedge.max;
        }
        break;
    default:
        break;
    }    
}

