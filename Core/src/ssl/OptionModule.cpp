#include "OptionModule.h"
#include <param.h>
#include "WorldModel/WorldModel.h"
#include "ParamManagerNew.h"

COptionModule::COptionModule()
{
	update();
	std::cout << "Side : " << ((_side == Param::Field::POS_SIDE_LEFT) ? "left" : "right")
		<< ", Color : " << ((_color == TEAM_YELLOW) ? "yellow" : "blue") << " is running..." << Param::Output::NewLineCharacter;
}

COptionModule::~COptionModule(void)
{

}


//too many couplings, can't use
void COptionModule::update() {
    bool isRightSide = OParamManager::Instance()->isRight;
    bool isYellowTeam = OParamManager::Instance()->isYellow;

	if (!isRightSide) {
		_side = Param::Field::POS_SIDE_LEFT;
	}
	else {
		_side = Param::Field::POS_SIDE_RIGHT;
	}

	if (isYellowTeam) {
		_color = TEAM_YELLOW;
	}
	else {
		_color = TEAM_BLUE;
    }
}
