#ifndef __DEFNCE_INFO_H__
#define __DEFNCE_INFO_H__

#include "singleton.h"
#include <vector>
#include <iostream>
#include "param.h"
#include "OppPlayer.h"
#include "geometry.h"
using namespace std;
// ?????????
typedef int oppNum;
typedef int ourNum;
typedef pair<oppNum,ourNum> MarkPair;
typedef vector<MarkPair> MarkList;        //?????,??????????????

class CVisionModule;
class CAttributeSet;
class CTrigger;

struct MarkField{
    MarkField(CGeoPoint upLeft, CGeoPoint downRight){_upLeft = upLeft; _downRight = downRight;}
    CGeoPoint _upLeft;
    CGeoPoint _downRight;
    int markTouchNum;//???????markTouch?©¦?
};

struct AttackerStruct{
    AttackerStruct(int n, int pri,double subV) : num(n), prioirty(pri),subValue(subV){}
    bool operator < (const AttackerStruct& n) const {
        if (prioirty < n.prioirty)//??????¬³???,???????
        {
            return true;
        } else if (n.prioirty == prioirty)
        {
            return subValue > n.subValue;//???????????????????????
        }
        return false;
    }
    int num;			// ????????
    int prioirty;	// ?????
    double subValue;//?????????
};
typedef std::vector< AttackerStruct > AttackerList;

class CDefenceInfo
{
public:
    CDefenceInfo();
    ~CDefenceInfo();
    void initialization();
    void updateDefenceInfo(const CVisionModule *pVision);

    void setNoChangeFlag();
    void clearNoChangeFlag();

    void setNoMarkingField(CGeoPoint upLeft, CGeoPoint downRight);
    void clearNoMarkingField(CGeoPoint upLeft, CGeoPoint downRight);
    void clearAll();
    void changeAttrSet(CAttributeSet& as);
    //?????????????¥ë??
    void setNoMarkingNum(int enemyNum);
    void resetMarkingInfo(){_normalNoMarkList.clear();}

public:
    int getOppoNum();
    int getAttackNum();
    int getAttackOppNumByPri(int i);
    int getSteadyAttackOppNumByPri(int i);
    bool queryMarked(int i){return _isMarked[i];}
    int getOurMarkDenfender(const int enemyNum);
    bool getMarkMode(const int enemy){return _markMode[enemy];}
    bool getTriggerState(){return _triggerOccur;}
    COppPlayer* getOppPlayerByNum(int i){return _oplayer[i];}
    bool getBallTaken(){return _ballTaken;}
    vector<MarkField> getMarkFieldList(){return _fieldList;}
    bool checkInRecArea(int enemyNum, const CVisionModule* pVision,MarkField markField);
    bool checkOurInRecArea(int myNum, const CVisionModule* pVision,MarkField markField);
    int getMarkingTouchNum(CGeoPoint upLeft,CGeoPoint downRight);

public:
    //???????
    void setMarkList(const CVisionModule* pVision,int myNum,int enemyNum);
    void setMarkingTouchInfo(const CVisionModule* pVision,int myNum,CGeoPoint upLeft,CGeoPoint rightDown);
    void setMarkMode(int myNum,int enemyNum,bool mode);
private:
    void updateAttackArray(const CVisionModule* pVision);
    void updateMarkPair(const CVisionModule* pVision);
    void updateSteadyAttackArray();
    void updateBallTaken(const CVisionModule* pVision);//???bestPlayer???????
    void checkSteadyAttack(const CVisionModule* pVision, AttackerList attackerList);
    int checkFieldAttack(MarkField markField, AttackerList attackerList);
    bool checkInAllField(int enemyNum);
    //bool checkInAllField(int enemyNum);

private:
    int _lastCycle;
    int _markCycle[Param::Field::MAX_PLAYER];
    MarkList _markList;
    bool _isMarked[Param::Field::MAX_PLAYER];
    bool _markMode[Param::Field::MAX_PLAYER];//?????????????????????

    int _oppoNum;										//????????????
    int _attackerNum;									//?????????????????,??????¬Ó????????????????????x???????
    int _attackArray[Param::Field::MAX_PLAYER];			//??????????????????·é*?????¬Ó??????????*
    int _steadyAttackArray[Param::Field::MAX_PLAYER];	//??????attackArray

    COppPlayer* _oplayer[Param::Field::MAX_PLAYER];
    vector<CTrigger*> _trigger;
    bool _triggerOccur;//????
    bool _ballTaken;

    vector<MarkField> _fieldList;
    vector<int> _noMarkList;
    CGeoPoint _upLeft;
    CGeoPoint _downRight;

    bool _noChangeFlag;
    COppPlayer* _noChangeOplayer[Param::Field::MAX_PLAYER];
    int _noChangeAttackArray[Param::Field::MAX_PLAYER];
    int _noChangeSteadyAttackArray[Param::Field::MAX_PLAYER];
    int _noChangeAttackNum;

    vector<int> _normalNoMarkList;

};

typedef Falcon::NormalSingleton<CDefenceInfo> DefenceInfo;

#endif
