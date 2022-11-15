#ifndef __DATA_RECEIVER4RBK_H__
#define __DATA_RECEIVER4RBK_H__
#include "WorldModel/WorldDefine.h"
#include "WorldModel/server.h"
#include "singleton.h"
#include "playmode.h"

class COptionModule;
class CDataReceiver4rbk{
public:
	CDataReceiver4rbk();
	~CDataReceiver4rbk(void);
	bool getGameInfo(const COptionModule *,GameInfoT&);//refrecvmsg仅用于更新进球数
private:
	bool rawVision2VisualInfo(const COptionModule *,GameInfoT&);
	PlayMode m_play_mode;
};
typedef NormalSingleton<CDataReceiver4rbk> DataReceiver4rbk;

#endif
