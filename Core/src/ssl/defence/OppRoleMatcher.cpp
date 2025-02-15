#include "OppRoleMatcher.h"
#include "OppPlayer.h"
#include "ClassFactory.h"
#include "OppRoleFactory.h"
#include <fstream>
#include <sstream>

namespace{
#ifdef WIN32
    const string CONFIG_PATH = "..\\data\\ssl\\defence_config\\";
#else
    const string CONFIG_PATH = "../data/ssl/defence_config/";
#endif
}
COppRoleMatcher::COppRoleMatcher()
{
    _oppRolePriList.clear();
    for (int i = 0 ; i < Param::Field::MAX_PLAYER ; ++i)_role[i] = new RNull();//??????????????1~6
    OppRoleFactory::Instance();
    readInConfig("TestOppRoleMatch.txt");
}

COppRoleMatcher::~COppRoleMatcher()
{
    for (OppRoleVector::iterator it = _oppRolePriList.begin(); it != _oppRolePriList.end(); ++it)
    {
        delete *it;
    }
    //delete []_role;
}

void COppRoleMatcher::readInConfig(std::string fileName)
{
    string fullFileName = CONFIG_PATH + fileName;
    ifstream infile(fullFileName.c_str());
    if (!infile)
    {
        cerr << "ERROR: there is no config file named " << fullFileName << endl;
        exit(-1);
    }
    for (OppRoleVector::iterator it = _oppRolePriList.begin(); it != _oppRolePriList.end(); ++it)
    {
        delete *it;
    }
    _oppRolePriList.clear();
    double mustIn,canIn,canOut,mustOut;
    int attack_threaten = PRIORITY_ATTACK;
    int defend_threaten = PRIORITY_DEFENCE;
    string line;
    string word;
    string name;
    while (getline(infile,line)){
        istringstream lineStream(line);
        lineStream;
        lineStream >> word >> name >> mustIn >> canIn >> canOut >> mustOut;
        OppRoleMap::iterator it = OppRoleFactory::Instance()->get()->find(name);
        if (OppRoleFactory::Instance()->get()->end() != it)
        {
            COppRole* role = (COppRole*)(ClassFactory::GetClassByName(name));
            bool roleRepeated = false;
            //??role??????
            for (OppRoleVector::iterator it2 = _oppRolePriList.begin(); it2 != _oppRolePriList.end() ; it2++)
            {
                if (role->getName() == (*it2)->getName())
                {
                    roleRepeated = true;
                    break;
                }
            }
            if (false == roleRepeated)
            {
                if ("ATTACKER" == word)
                {
                    role->SetProperty(attack_threaten,mustIn,canIn,canOut,mustOut);
                    ++attack_threaten;
                } else if ("DEFENDER" == word)
                {
                    role->SetProperty(defend_threaten,mustIn,canIn,canOut,mustOut);
                    ++defend_threaten;
                }
                _oppRolePriList.push_back(role);
            }else{
                cout << "ERROR: the role named " << name <<" has already been in role list " << endl;
            }
        } else {
            cout << "ERROR: there is not a role named " << name << "!!!" << endl;
        }
    }
}

//?????��???????????????
COppRole* COppRoleMatcher::matchRole(COppPlayer& oplayer)
{
    int num = oplayer._num;
    //wrong number
    if (num < 0 || num >= Param::Field::MAX_PLAYER)
    {
        cout << "ERROR: wrong num with opp role match!!!" << endl;
        return NULL;
    }
    //first calc
    _role[num]->calcSubValue(oplayer._attrSetP);//???subValue?????????????????????????
    //??????????role???????mustChangeIn?????change
    for (OppRoleVector::iterator it = _oppRolePriList.begin() ; it != _oppRolePriList.end() ; ++it)
    {
        (*it)->calcSubValue(oplayer._attrSetP);//??????????????��???
        if ((*it)->mustChangeIn() && (*it)->getName() != _role[num]->getName())
        {
            if ((*it)->getThreatenPri() <= _role[num]->getThreatenPri() || !_role[num]->canChangeIn())
            {
                return change(it,num);
            }
        }
    }
    //??????????????????��???
    if (false == _role[num]->mustChangeIn())
    {
        if (_role[num]->mustChangeOut())
        {
            //??????canChangeIn?????change
            for (OppRoleVector::iterator it = _oppRolePriList.begin() ; it != _oppRolePriList.end() ; ++it)
            {
                if ((*it)->canChangeIn())
                {
                    return change(it,num);
                }
            }
            //?????????canChangeIn?????��???????canChangeOut??????change
            for (OppRoleVector::iterator it = _oppRolePriList.begin() ; it != _oppRolePriList.end() ; ++it)
            {
                if (!(*it)->canChangeOut())
                {
                    return change(it,num);
                }
            }
            //?????????canChangeOut????????��???????????mustChangeOut???change
            for (OppRoleVector::iterator it = _oppRolePriList.begin() ; it != _oppRolePriList.end() ; ++it)
            {
                if (!(*it)->mustChangeOut())
                {
                    return change(it,num);
                }
            }
        }
        else if (_role[num]->canChangeOut())
        {
            //??????canChangeIn?????change
            for (OppRoleVector::iterator it = _oppRolePriList.begin() ; it != _oppRolePriList.end() ; ++it)
            {
                if ((*it)->canChangeIn())
                {
                    return change(it,num);
                }
            }
        }
    }
    return _role[num];
}

COppRole* COppRoleMatcher::change(OppRoleVector::iterator it, int num)
{
    delete _role[num];
    _role[num] = (COppRole*)(ClassFactory::GetClassByName((*it)->getName()));
    _role[num]->SetProperty((*it)->_threatenPri,(*it)->_mustChangeIn,(*it)->_canChangeIn,(*it)->_canChangeOut,(*it)->_mustChangeOut);
    _role[num]->_subValue = (*it)->_subValue;
    return _role[num];
}





