/**
#include "networkinterfaces.h"
#include "visionmodule.h"
CNetworkInterfaces::CNetworkInterfaces(QObject *parent) : QObject(parent)
{

}
void CNetworkInterfaces::updateInterfaces(){
    this->interfaces.clear();
    for(auto interface : QNetworkInterface::allInterfaces()){
        interfaces.append(interface.humanReadableName());
    }
}
void CNetworkInterfaces::changeVisionInterface(int index){
    VisionModule::Instance()->setInterfaceIndex(index);
}
**/