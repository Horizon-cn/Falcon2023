#include "DefenceInfo.h"
#include "param.h"
#include "AttributeSet.h"
#include "Trigger.h"
#include "OppPlayer.h"
#include "OppRole.h"
#include "OppRoleMatcher.h"
#include "Vision/VisionModule.h"
#include "TaskMediator.h"
#include "OppAttributesFactory.h"
#include "GDebugEngine.h"
#include "defenceNew/DefenceInfoNew.h"
#include <cstring>

namespace{
	bool DEFENCE_DEBUG_MODE;
	bool ATTACK_DEF_MODE;
	bool GOALIE_EVALUATE;
	const double ballTakedDist = Param::Vehicle::V2::PLAYER_FRONT_TO_CENTER + 5; //是否拿球拿稳的距离判据
	const double ballTakedAngle = Param::Math::PI / 3.0;						 //是否拿球拿稳的角度判据
}
RegisterPair ClassFactory::m_vec[];
CDefenceInfo::CDefenceInfo(){
	DEFENCE_DEBUG_MODE = paramManager->DEFENCE_DEBUG_MODE;
	ATTACK_DEF_MODE = paramManager->ATTACK_DEF_MODE;
	GOALIE_EVALUATE = paramManager->GOALIE_EVALUATE;
	_lastCycle = 0;
	for(int i = 0;i < Param::Field::MAX_PLAYER;i++)_markCycle[i] = 0;
	for(int i = 0;i < Param::Field::MAX_PLAYER;i++)_isMarked[i] = false;
	for(int i = 0;i < Param::Field::MAX_PLAYER;i++)_markMode[i] = false;
	_markList.reserve(Param::Field::MAX_PLAYER);
	_markList.clear();
	_trigger.clear();

	_oppoNum = 0;
	_attackerNum = 0;
	for(int i = 0;i < Param::Field::MAX_PLAYER;i++)_attackArray[i] = 0;
	for(int i = 0;i < Param::Field::MAX_PLAYER;i++)_steadyAttackArray[i] = 0;
    for(int i = 0;i < Param::Field::MAX_PLAYER;i++)_oplayer[i] = new COppPlayer();
	initialization();
	_ballTaken = false;
	
	_upLeft = CGeoPoint(0,0);
	_downRight = CGeoPoint(0,0);
	_noChangeFlag = false;
	_normalNoMarkList.clear();

	_noChangeAttackNum = 0;
	for(int i = 0;i < Param::Field::MAX_PLAYER;i++)_noChangeAttackArray[i] = 0;
    for(int i = 0;i < Param::Field::MAX_PLAYER;i++)_noChangeOplayer[i] = new COppPlayer();
}

CDefenceInfo::~CDefenceInfo()
{
    // delete [] _oplayer;
    // delete [] _noChangeOplayer;
}

void CDefenceInfo::changeAttrSet(CAttributeSet& as)
{
	for (int i = 0; i < Param::Field::MAX_PLAYER;++i)
	{
        _oplayer[i]->setProperty(i,as);
	}
}

void CDefenceInfo::initialization(){
	//1.config attribute_set
	AttributeFactory::Instance();

	//2. opp_player get attrset
	changeAttrSet(*(AttributeFactory::Instance()->get()));

	//3.init oppRoleMatcher
	OppRoleMatcher::Instance();

	//4.init trigger
	_trigger.push_back(new TKeeperChanged());
	_trigger.push_back(new TAttackerChanged());
	_trigger.push_back(new TReceiverNoMarked());
	//_trigger.push_back(new TReceiverNoMarked2());
	for (vector<CTrigger*>::iterator it = _trigger.begin(); it != _trigger.end()-1;++it)
	{
		(*it)->setNext(*(it+1));
	}
}

void CDefenceInfo::updateDefenceInfo(const CVisionModule *pVision){
	for (int i = 0; i < Param::Field::MAX_PLAYER;i++)
	{
		if (pVision->TheirPlayer(i).Valid())
		{
			//cout<<"saaaaa "<<i<<endl;
            _oplayer[i]->evaluate(pVision);
            _oplayer[i]->matchRole();
		}		
	}
	//更新进攻序列
	updateAttackArray(pVision);	
	//更新盯人对
	updateMarkPair(pVision);
	//更新BestPlayer持球状态
	updateBallTaken(pVision);
	//更新触发信号
	_triggerOccur = (*_trigger.begin())->handler(pVision);
	if (_triggerOccur)updateSteadyAttackArray();

	_lastCycle = pVision->Cycle();
	if (DEFENCE_DEBUG_MODE)
	{
		//cout << "attack array is ";
        int attcnt = getAttackNum();
        QString attackInform;
        attackInform.append(QString("attackInform: %1:").arg(attcnt));
        for(int i = 0; i < attcnt; i++)
            attackInform.append(QString(" %1").arg(_attackArray[i]));
        QString attackSteadyInform;
        attackSteadyInform.append(QString("steady attack:"));
        for(int i = 0; i < attcnt; i++)
            attackSteadyInform.append(QString(" %1").arg(_steadyAttackArray[i]));
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(100, -450),attackInform.toLatin1(),COLOR_YELLOW);
        GDebugEngine::Instance()->gui_debug_msg(CGeoPoint(-400,-450),attackSteadyInform.toLatin1(),COLOR_YELLOW);
		for (int i = 0; i < Param::Field::MAX_PLAYER; ++i)
		{
			//cout << _attackArray[i-1];
		
			CGeoPoint playerPos = pVision->TheirPlayer(i).Pos();
			char oppRoleName[2];
            oppRoleName[0] = _oplayer[i]->getRoleName().c_str()[1];
			oppRoleName[1] = 0;
			GDebugEngine::Instance()->gui_debug_msg(playerPos, oppRoleName, COLOR_YELLOW);
			/*
			char roleinfo[50];
			char subvalue[50];
			memset(roleinfo, 0, 50);
			memset(subvalue, 0, 50);
			sprintf(roleinfo, "%s %d", _oplayer[i]->getRoleName().c_str(), _oplayer[i]->getThreatenPri());
			sprintf(subvalue, "[%f]", _oplayer[i]->getThreatenValue());
			GDebugEngine::Instance()->gui_debug_msg(playerPos + CVector(5, 5),roleinfo,COLOR_YELLOW);
			GDebugEngine::Instance()->gui_debug_msg(playerPos + CVector(-15, 0),subvalue,COLOR_CYAN);
			*/
			
            double  t = _oplayer[i]->getThreatenValue();
            QString roleValue;
            roleValue = QString("%1").arg(t);
            //GDebugEngine::Instance()->gui_debug_msg(playerPos+CVector(-20,0),roleValue,COLOR_WHITE);
		}
	}
}

bool CDefenceInfo::checkInAllField(int enemyNum)
{
	vector<MarkField>:: iterator ir;
	bool result = false;
	for (ir = _fieldList.begin();ir != _fieldList.end();ir++){
		if (checkInRecArea(enemyNum,vision,*ir)){
			result = true;
			break;
		}
	}
	return result;
}

int CDefenceInfo::getOurMarkDenfender(const int enemyNum)
{
	int defender = 0;
	for (MarkList::iterator it = _markList.begin();it != _markList.end();it++)
	{
		if (it->first == enemyNum)
		{
			defender = it->second;
			break;
		}
	}
	return defender;
}

void CDefenceInfo::setMarkList(const CVisionModule* pVision,int myNum,int enemyNum)
{
	if (!pVision->OurPlayer(myNum).Valid() || !pVision->TheirPlayer(enemyNum).Valid())
	{
		if (0 == enemyNum)//可能会有问题，暂时这样处理 TODO
		{
			return;
		}
		cout<<"Wrong vehicle num in set MarkList,please check"<<endl;
		return;
	}
	_markCycle[enemyNum] = pVision->Cycle();
	for (MarkList::iterator it = _markList.begin();it != _markList.end();it++)
	{
		if (it->first == enemyNum)
		{
			_markList.erase(it);
			break;
		}
	}
	_markList.push_back(MarkPair(enemyNum,myNum));	
	_isMarked[enemyNum] = true;
}

void CDefenceInfo::setMarkMode(int myNum,int enemyNum,bool mode){
	_markMode[enemyNum] =mode;
}

void CDefenceInfo::setMarkingTouchInfo(const CVisionModule* pVision,int myNum,CGeoPoint upLeft,CGeoPoint rightDown)
{
	vector<MarkField>::iterator ir;
	if (_fieldList.size()!=0){
		for (ir = _fieldList.begin();ir != _fieldList.end();ir++){
			if (upLeft == (*ir)._upLeft && rightDown == (*ir)._downRight){
				(*ir).markTouchNum = myNum;
			}
		}
	}
}

void CDefenceInfo::updateAttackArray(const CVisionModule* pVision)
{
	memset(_attackArray,0,sizeof(_attackArray));
	AttackerList attackerTempList;
	_oppoNum = 0;
	_attackerNum = 0;
	for (int i = 0;i < Param::Field::MAX_PLAYER;++i)
	{
		if (!pVision->TheirPlayer(i).Valid())continue;
		_oppoNum += 1;
        if (_oplayer[i]->getThreatenPri() < PRIORITY_DEFENCE)
		{
            attackerTempList.push_back(AttackerStruct(i,_oplayer[i]->getThreatenPri(),_oplayer[i]->getThreatenValue()));
		}
	}
	if (0 != attackerTempList.size())
	{
		std::sort(attackerTempList.begin(),attackerTempList.end());
		//ATTACK_DEF_MODE长期打开
		if(ATTACK_DEF_MODE){
			vector<MarkField>::iterator fr;
			//cout<<"fieldlistsize is "<<_fieldList.size()<<endl;
			_noMarkList.clear();
			for (fr = _fieldList.begin();fr != _fieldList.end();fr++){
				if (checkFieldAttack(*fr,attackerTempList) !=0){
					_noMarkList.push_back(checkFieldAttack(*fr,attackerTempList));
				}
			}
			AttackerList::iterator it;
			vector<int>::iterator ir;
			for (ir = _noMarkList.begin();ir != _noMarkList.end();ir++){
				for(it = attackerTempList.begin();it != attackerTempList.end();){
					if (it->num == *ir){
						it = attackerTempList.erase(it);
					} else{
						it++;
					}
				}
			}
			//清除开球区域的挡位车
			WorldModel::Instance()->getEnemyKickOffNum();
			for(vector<int>::iterator pr=_normalNoMarkList.begin();pr!=_normalNoMarkList.end();pr++){
				for(AttackerList::iterator tt = attackerTempList.begin();tt != attackerTempList.end();){
					if (tt->num == *pr){
						tt = attackerTempList.erase(tt);
					} else{
						tt++;
					}
				}
			}
			//清除守门员于列表中，如果GOALIE_EVALUATE为true
			if (GOALIE_EVALUATE == true) {
                //if (pVision->gameState().gameOn()) {
					int goalieNum = vision->TheirGoalie();
					//int goalieNum = 3;
					for (AttackerList::iterator tt = attackerTempList.begin(); tt != attackerTempList.end();) {
						if (tt->num == goalieNum) {
							tt = attackerTempList.erase(tt);
						} else {
							tt++;
						}
					}
                //}
			}

			checkSteadyAttack(pVision,attackerTempList);
		}
		_attackerNum = attackerTempList.size();
		int tempCount = 0;
		if (_attackerNum > 0){
			for (AttackerList::iterator it = attackerTempList.begin();it != attackerTempList.end();it++)
			{
				_attackArray[tempCount] = it->num;
				tempCount++;
			}
		}
	}
}

void CDefenceInfo::setNoMarkingNum(int enemyNum)
{
	bool setFlag = false;
	for(vector<int>::iterator tr=_normalNoMarkList.begin();tr!=_normalNoMarkList.end();tr++){
		if (*tr == enemyNum){
			setFlag = true;
			break;
		}
	}
	if (setFlag ==false){
		_normalNoMarkList.push_back(enemyNum);
	}
}

void CDefenceInfo::updateMarkPair(const CVisionModule* pVision)
{
	for (int i = 0;i < Param::Field::MAX_PLAYER;i++)
	{
		if (!pVision->TheirPlayer(i).Valid() )				          
		{
			continue;
		}
		if (pVision->Cycle() - _markCycle[i] > 5)
		{
			for (MarkList::iterator it = _markList.begin();it != _markList.end();it++)
			{
				if (it->first == i)
				{
					_markList.erase(it);
					_isMarked[i] = false;
					break;
				}
			}
		}
	}
}

void CDefenceInfo::updateSteadyAttackArray()
{
	for(int i = 0;i < Param::Field::MAX_PLAYER;i++)_steadyAttackArray[i] = _attackArray[i];
}

void CDefenceInfo::updateBallTaken(const CVisionModule* pVision)
{
	int keeperNum = DefenceInfoNew::Instance()->getBestBallChaser();
	const PlayerVisionT& keeper =pVision->TheirPlayer(keeperNum);
	const CGeoPoint ballPos = pVision->Ball().Pos();
	static int ballTakedCount = 0;
	static int ballUnTakedCount = 0;
	if (keeper.Pos().dist(ballPos) < ballTakedDist &&
		fabs(Utils::Normalize(keeper.Dir() - CVector(ballPos - keeper.Pos()).dir())) < ballTakedAngle)
	{
		ballTakedCount++;
		ballUnTakedCount = 0;		
	}else{
		ballUnTakedCount++;
		ballTakedCount = 0;
	}
	ballTakedCount = ballTakedCount <= 100 ? ballTakedCount : 100;
	ballUnTakedCount = ballUnTakedCount <= 100 ? ballUnTakedCount : 100;
	if (ballTakedCount > 10)
	{
		_ballTaken = true;
	} 
	else if (ballUnTakedCount > 5)
	{
		_ballTaken= false;
	}
}

bool CDefenceInfo::checkInRecArea(int enemyNum, const CVisionModule* pVision, MarkField markField)
{
	bool result = false;
	if (enemyNum!=0){
		double x = pVision->TheirPlayer(enemyNum).X();
		double xmax = markField._upLeft.x();
		double xmin = markField._downRight.x();
		double y = pVision->TheirPlayer(enemyNum).Y();
		double ymin = markField._upLeft.y();
		double ymax = markField._downRight.y();
		if (x>=xmin && x<=xmax && y>=ymin && y<=ymax){
			result = true;
		}
	}
	return result;
}

bool CDefenceInfo::checkOurInRecArea(int myNum, const CVisionModule* pVision, MarkField markField)
{
	bool result = false;
	if (myNum!=0){
		double x = pVision->OurPlayer(myNum).X();
		double xmax = markField._upLeft.x();
		double xmin = markField._downRight.x();
		double y = pVision->OurPlayer(myNum).Y();
		double ymin = markField._upLeft.y();
		double ymax = markField._downRight.y();
		if (x>=xmin && x<=xmax && y>=ymin && y<=ymax){
			result = true;
		}
	}
	return result;
}

int CDefenceInfo::checkFieldAttack(MarkField markField, AttackerList attackerList){
	AttackerList::iterator it;
	vector<int> tmpList;
	for (it = attackerList.begin();it != attackerList.end();it++){
		if (checkInRecArea(it->num,vision,markField)){
			tmpList.push_back(it->num);
		}
	}
	vector<int>::iterator ir;
	double tm =1000;
	int result = 0;
	if (tmpList.size()!=0){
		for (ir = tmpList.begin();ir!= tmpList.end();ir++){
			if (vision->TheirPlayer(*ir).Pos().dist(vision->Ball().Pos())<tm){
				tm = vision->TheirPlayer(*ir).Pos().dist(vision->Ball().Pos());
				result =*ir;
			}
		}
	}
	return result;
}

void CDefenceInfo::setNoMarkingField(CGeoPoint upLeft, CGeoPoint downRight)
{
	MarkField field = MarkField(upLeft, downRight);
	field.markTouchNum = 0;
	bool result = false;
    vector<MarkField>::iterator ir;
	for (ir = _fieldList.begin();ir!=_fieldList.end();ir++){
		if (fabs((*ir)._upLeft.x()-upLeft.x())<0.1 &&fabs((*ir)._upLeft.y()-upLeft.y())<0.1 && fabs((*ir)._downRight.x() - downRight.x())<0.1
			&& fabs((*ir)._downRight.y() - downRight.y())<0.1){
			result = true;
			break;
		}
	}
	if (result == false){
		_fieldList.push_back(field);
	}
}

void CDefenceInfo::clearNoMarkingField(CGeoPoint upLeft, CGeoPoint downRight)
  {
	vector<MarkField>::iterator ir;
	if (_fieldList.size()!=0){
		for (ir = _fieldList.begin();ir != _fieldList.end();){
			if (fabs((*ir)._upLeft.x()-upLeft.x())<0.1 &&fabs((*ir)._upLeft.y()-upLeft.y())<0.1 && fabs((*ir)._downRight.x() - downRight.x())<0.1
				&& fabs((*ir)._downRight.y() - downRight.y())<0.1){
				ir = _fieldList.erase(ir);
			}else{
				ir++;
			}
		}
	}
}

void CDefenceInfo::clearAll()
{
	_fieldList.clear();
}

void CDefenceInfo::checkSteadyAttack(const CVisionModule* pVision, AttackerList attackerList)
{
	int tmpSteadyAttack[Param::Field::MAX_PLAYER] = {0,0,0,0,0,0,0,0};
	int index = 0;
	for (int i =0;i< Param::Field::MAX_PLAYER;i++){
		for (AttackerList::iterator ar = attackerList.begin();ar != attackerList.end();ar++){
			if (_steadyAttackArray[i] == (*ar).num){
				tmpSteadyAttack[index] = _steadyAttackArray[i];
				index++;
			}
		}
	}
	for (int i=0;i<Param::Field::MAX_PLAYER;i++){
		_steadyAttackArray[i] = 0;
	}
	for (int i=0;i<index;i++){
		_steadyAttackArray[i] = tmpSteadyAttack[i];
	}
}

int CDefenceInfo::getMarkingTouchNum(CGeoPoint upLeft,CGeoPoint downRight)
{
	vector<MarkField>::iterator ir;
	//cout<<"fieldList size is "<<_fieldList.size()<<endl;
	if (_fieldList.size()!=0){
		for (ir = _fieldList.begin();ir != _fieldList.end();ir++){
			if (upLeft == (*ir)._upLeft && downRight == (*ir)._downRight){
				if((*ir).markTouchNum!=0){
					return (*ir).markTouchNum;
				}
			}
		}
	}
	return 0;
}

void CDefenceInfo::setNoChangeFlag()
{
	_noChangeFlag = true;
	for (int i = 0; i < Param::Field::MAX_PLAYER;i++)
	{
		_noChangeOplayer[i] = _oplayer[i];
		_noChangeAttackArray[i] = _attackArray[i];
		_noChangeSteadyAttackArray[i] = _steadyAttackArray[i];
		_noChangeAttackNum = _attackerNum;
		//cout<<_noChangeAttackArray[i-1];
	}
	//cout<<endl;
}

void CDefenceInfo::clearNoChangeFlag()
{
	//cout<<"in clear"<<endl;
	_noChangeFlag = false;
}

int CDefenceInfo::getOppoNum()
{
	return _oppoNum;
}

int CDefenceInfo::getAttackNum()
{
	if(_noChangeFlag == false){
		return _attackerNum;
	}else{
		return _noChangeAttackNum;
	}
}

int CDefenceInfo::getAttackOppNumByPri(int i)
{
	if (_noChangeFlag == false){
		return _attackArray[i];
	}else{
		return _noChangeAttackArray[i];
	}
}

int CDefenceInfo::getSteadyAttackOppNumByPri(int i)
{
	if(_noChangeFlag == false){
		return _steadyAttackArray[i];
	}else{
		return _noChangeSteadyAttackArray[i];
	}
}
