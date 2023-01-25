#ifndef STATICPARAMS_H
#define STATICPARAMS_H
//change param for 2018 rule
//wait for change camera number
#include <QString>
namespace PARAM {
	const int CAMERA = 8;
	const int ROBOTMAXID = 16;
	const int BALLNUM = 20;
	const int BLUE = 0;
	const int YELLOW = 1;
	const int TEAMS = 2;
	const int PROCESS = 4;
	const int SIM = 2; //sim process
//	const int CRAY = 3; //Cray process
}
namespace Vision {
	const int CAMERA_STORE_BUFFER = 100;
	const int BALL_STORE_BUFFER = 100;
	const int ROBOT_STORE_BUFFER = 100;
	const int MAINTAIN_STORE_BUFFER = 1000;
	const int COMMAND_STORE_BUFFER = 1000;
}
#endif // STATICPARAMS_H
