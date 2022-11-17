#include "GoTechChalPos.h"
#include "GDebugEngine.h"
#include <Vision/VisionModule.h>
#include "RobotSensor.h"
#include "skill/Factory.h"
#include <MotionControl/ControlModel.h>
#include <utils.h>
#include <WorldModel/DribbleStatus.h>
#include <MotionControl/ControlModel.h>
#include "GDebugEngine.h"
#include "TaskMediator.h"
#include "BestPlayer.h"
#include <string>
#include <ctime>
#include <algorithm>

CGoTechChalPos::CGoTechChalPos() {
}

void CGoTechChalPos::plan(const CVisionModule* pVision) {
    const int _executor = task().executor;
    const PlayerVisionT& me = pVision->OurPlayer(_executor);
    const BallVisionT& ball = pVision->Ball();
    //const CGeoPoint

    setSubTask(PlayerRole::makeItChaseKickV2(_executor, 0));
    CStatedTask::plan(pVision);
}
//execute
CPlayerCommand* CGoTechChalPos::execute(const CVisionModule* pVision) {
    if (subTask()) {
        return subTask()->execute(pVision);
    }
    return NULL;
}
