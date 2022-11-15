#include "OptionModule.h"
#include <param.h>
#include "WorldModel/WorldModel.h"
#include <robokit/core/rbk_config.h>

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
	auto pParamManager = rbk::ParamsServer::Instance()->find("ParamManager");
	std::string value;
	pParamManager->get("IsRight", value);
	bool isRightSide = value == "0" ? 0 : 1;
	pParamManager->get("IsYellow", value);
	bool isYellowTeam = value == "0" ? 0 : 1;

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
	//std::cout << "Side : " << ((_side == Param::Field::POS_SIDE_LEFT) ? "left" : "right")
	//	<< ", Color : " << ((_color == TEAM_YELLOW) ? "yellow" : "blue") << " is running..." << Param::Output::NewLineCharacter;
}