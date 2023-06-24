#include "globalsettings.h"
#include "field.h"
#include "parammanager.h"
namespace{
    auto opm = Owl::OParamManager::Instance();
    auto vpm = Owl::VParamManager::Instance();
    auto cpm = Owl::CParamManager::Instance();
}
CGlobalSettings::CGlobalSettings(QObject *parent):QObject(parent),minimumX(-999999),minimumY(-999999),maximumX(999999),maximumY(999999){

}
bool CGlobalSettings::inChosenArea(float x, float y){
    return (x >= minimumX && x <= maximumX && y >= minimumY && y <= maximumY);
}
bool CGlobalSettings::inChosenArea(CGeoPoint point){
    return (point.x() >= minimumX && point.x() <= maximumX && point.y() >= minimumY && point.y() <= maximumY);
}
void CGlobalSettings::setArea(float a,float b,float c,float d){
    minimumX = a;
    minimumY = c;
    maximumX = b;
    maximumY = d;
}
void CGlobalSettings::resetArea(){
    minimumX = -opm->param_canvasWidth/2;
    minimumY = -opm->param_canvasHeight/2;
    maximumX = opm->param_canvasWidth/2;
    maximumY = opm->param_canvasHeight/2;
}
void CGlobalSettings::setBallPlacementPos(float x,float y){
    ballPlacementX = x;
    ballPlacementY = y;
}
/**
 * @brief convert position between different field size
 * @param originPoint
 * @return
 */
CGeoPoint CGlobalSettings::saoConvert(CGeoPoint originPoint) {
    CGeoPoint result;
    switch (opm->saoAction) {
    case 0:
        //default
        result.setX(originPoint.x());
        result.setY(originPoint.y());
        break;
    case 1:
        //convert small field to half big field(right)
        result.setX(originPoint.y() + 3000);
        result.setY(-originPoint.x());
        break;
    case 2:
        //convert small field to half big field(left)
        result.setX(-originPoint.y() - 3000);
        result.setY(originPoint.x());
        break;
    case 3:
        //convert small field to whole big field
        result.setX(originPoint.x() * 4 / 3);
        result.setY(originPoint.y() * 3 / 2);
        break;        
    case 4:
        result.setX(-originPoint.x());
        result.setY(-originPoint.y());
        break;    
    case 5:
        //convert small field to big field (penalty area)
        result.setX(originPoint.x() + 1500);
        result.setY(originPoint.y());
        break;
    default:
        result.setX(originPoint.x());
        result.setY(originPoint.y());
        break;
    }
    return result;
}
/**
 * @brief convert angle between different field size
 * @param direction
 * @return
 */
double CGlobalSettings::saoConvert(double direction) {
    double result;
    switch (opm->saoAction) {
    case 0:
        result = direction;
        break;
    case 1:
        result = direction - cpm->PI / 2;
        break;
    case 2:
        result = direction + cpm->PI / 2;
        break;
    case 3:
        // there maybe some problems with original direction 
        if(fabs(direction) > cpm->PI / 2 && fabs(direction) < 3* cpm->PI / 2)
            result = atan(9/8*tan(direction)) + cpm->PI;
        else
            result = atan(9/8*tan(direction));
        break;
    case 4:
        result = direction;
        break;
    case 5:
        result = direction;
        break;
    default:
        result = direction;
        break;
    }
    return result;
}
