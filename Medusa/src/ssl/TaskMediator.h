#ifndef _TASK_MEDIATOR_H_
#define _TASK_MEDIATOR_H_

#include <singleton.h>
#include <geometry.h>
#include <param.h>
#include <skill/PlayerTask.h>
#include "utils.h"
#include "Global.h"
/**
* task§¿????.
* ???????????????????????????????????????§¿????????
*/

struct SpecialRole{
    SpecialRole() : num(0), lastCycle(0){}
    int num;
    int lastCycle;
};

class CTaskMediator{
public:
    CTaskMediator() : _ballHandler(0)
    {
        USE_LUA_SCRIPTS = true;
        for(int i=0; i<Param::Field::MAX_PLAYER; ++i ){
            _playerTask[i] = 0;
        }
    }
    // ???????
    void setBallHandler(int num){ _ballHandler = num; }
    int ballHandler() const { return _ballHandler; }

    // ?????
    int goalie(){
        if(USE_LUA_SCRIPTS){
            return _goalie.num;
        }else{
            // need to be checked by zhyaic 2014.2.19
            return _goalie.num;
            //return PlayInterface::Instance()->getRealIndexByNum(PlayMediator::Instance()->getRealRobotNum("Goalie"));
        }
    }

    // ??????
    int leftBack(){
        if(vision->Cycle() - _leftBack.lastCycle > 5){
            _leftBack.num = 0;
        }
        return _leftBack.num;
    }

    // ?????
    int rightBack(){
        if(vision->Cycle() - _rightBack.lastCycle > 5){
            _rightBack.num = 0;
        }
        return _rightBack.num;
    }

    //???§Ü???
    int leftCenterBack() {
        if (vision->Cycle() - _leftCenterBack.lastCycle > 5) {
            _leftCenterBack.num = 0;
        }
        return _leftCenterBack.num;
    }

    //???§Ü???
    int rightCenterBack() {
        if (vision->Cycle() - _rightCenterBack.lastCycle > 5) {
            _rightCenterBack.num = 0;
        }
        return _rightCenterBack.num;
    }

    // ??????
    int singleBack(){
        if(vision->Cycle() - _singleBack.lastCycle > 5){
            _singleBack.num = 0;
        }
        return _singleBack.num;
    }

    // ???????
    int defendMiddle(){
        if(vision->Cycle() - _defendMiddle.lastCycle > 5){
            _defendMiddle.num = 0;
        }
        return _defendMiddle.num;
    }

    //?????
    int sideBack(){
        if(vision->Cycle() - _sideBack.lastCycle > 5){
            _sideBack.num = 0;
        }
        return _sideBack.num;
    }

    int advancer(){
        if (vision->Cycle() - _advancer.lastCycle> 5){
            _advancer.num = 0;
        }
        return _advancer.num;
    }

    bool isGoalie(int vecNumber) {
        return (goalie() == vecNumber);
    }

    bool isBack(int vecNumber) {
        return ((vecNumber == leftBack())    ||
                (vecNumber == rightBack())   ||
                (vecNumber == singleBack())  ||
                (vecNumber == sideBack())    ||
                (vecNumber == defendMiddle()));
    }

    bool isMultiBack(int vecNumber) {
        if (vision->Cycle() - _multiBack[vecNumber].lastCycle > 10)
            _multiBack[vecNumber].num = false;
        return _multiBack[vecNumber].num;
    }

    void setMultiBack(const int num)
    {
        _multiBack[num].num = true;
        _multiBack[num].lastCycle = vision->Cycle();
    }

    // ????
    void setPlayerTask(const int num, CPlayerTask* pTask, const int priority)
    {
        if (Utils::PlayerNumValid(num)){
            _playerTaskPriority[num] = priority;
            _playerTask[num] = pTask;
        }
    }

    CPlayerTask* getPlayerTask(const int num) const
    {
        if (Utils::PlayerNumValid(num)){
            return _playerTask[num];
        }else{
            return NULL;
        }
    }

    int getPlayerTaskPriority(const int num) const
    {
        if (Utils::PlayerNumValid(num)){
            return _playerTaskPriority[num];
        }else{
            return -1;
        }
    }

    void cleanOldTasks()
    {
        // ??????¨²?????,??????úY?false, ???????????Ú…??????????¦Ë?????, ???????¦Ë??????.
        for(int num=0; num<Param::Field::MAX_PLAYER; ++num ){
            _playerTask[num] = 0;
        }
    }

    void setRoleInLua(int num, string role)
    {
        if("goalie" == role){
            _goalie.num = num;
            _goalie.lastCycle = vision->Cycle();
        } else if ("leftBack" == role){
            _leftBack.num = num;
            _leftBack.lastCycle = vision->Cycle();
        } else if ("rightBack" == role){
            _rightBack.num = num;
            _rightBack.lastCycle = vision->Cycle();
        }else if ("leftCenterBack" == role) {      //???????§Ü????§Ø?
            _leftCenterBack.num = num;
            _leftCenterBack.lastCycle = vision->Cycle();
        }else if ("rightCenterBack" == role) {       //???????§Ü????§Ø?
            _rightCenterBack.num = num;
            _rightCenterBack.lastCycle = vision->Cycle();
        }else if ("singleBack" == role){
            _singleBack.num = num;
            _singleBack.lastCycle = vision->Cycle();
        } else if ("defendMiddle" == role){
            _defendMiddle.num = num;
            _defendMiddle.lastCycle = vision->Cycle();
        } else if ("sideBack" == role){
            _sideBack.num = num;
            _sideBack.lastCycle = vision->Cycle();
        }else if ("advancer" == role){
            _advancer.num = num;
            _advancer.lastCycle = vision->Cycle();
        }else{
            cout<<"Error In setRoleInLua!!!  "<<role<<endl;
        }
    }
private:
    bool USE_LUA_SCRIPTS;
    SpecialRole _goalie;
    SpecialRole _leftBack;
    SpecialRole _rightBack;
    SpecialRole _leftCenterBack;
    SpecialRole _rightCenterBack;
    SpecialRole _singleBack;
    SpecialRole _defendMiddle;
    SpecialRole _sideBack;
    SpecialRole _advancer;
    SpecialRole _multiBack[Param::Field::MAX_PLAYER];
    int _ballHandler; // ???????
    CPlayerTask* _playerTask[Param::Field::MAX_PLAYER]; // ?????????
    int _playerTaskPriority[Param::Field::MAX_PLAYER]; // ??????????????
};
typedef NormalSingleton< CTaskMediator > TaskMediator;

#endif // _TASK_MEDIATOR_H_
