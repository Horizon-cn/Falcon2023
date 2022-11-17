TEMPLATE = app

CONFIG += c++11

QT += core qml quick network

CONFIG += c++11 console

DEFINES += QT_DEPRECATED_WARNINGS

# python module for windows and linux
# if you change this switch, you may need to clear the cache
#DEFINES += USE_PYTHON_MODULE
#DEFINES += USE_CUDA_MODULE
#DEFINES += USE_OPENMP

ZSS_LIBS =
ZSS_INCLUDES =

CONFIG(debug, debug|release) {
    #CONFIG += console
    TARGET = MedusaD
    DESTDIR = $$PWD/../ZBin
    MOC_DIR = ./temp
    OBJECTS_DIR = ./temp
}
CONFIG(release, debug|release) {
    TARGET = Medusa
    DESTDIR = $$PWD/../ZBin
    MOC_DIR = ./temp
    OBJECTS_DIR = ./temp
}

win32 {
    if(contains(DEFINES,USE_OPENMP)){
        QMAKE_CXXFLAGS += -openmp
    }
    win32-msvc*:QMAKE_CXXFLAGS += /wd"4819"
    # Third party library dir
    THIRD_PARTY_DIR = $$PWD/../ZBin/3rdParty
    contains(QMAKE_TARGET.arch, x86_64){
        message("64-bit")
        CONFIG(release,debug|release){
            ZSS_LIBS += $${THIRD_PARTY_DIR}/protobuf/lib/x64/libprotobuf.lib \
                        $${THIRD_PARTY_DIR}/tolua++/lib/x64/tolua++.lib \
                        $${THIRD_PARTY_DIR}/lua/lib/x64/lua5.1.lib
        }
        CONFIG(debug,debug|release){
            ZSS_LIBS += $${THIRD_PARTY_DIR}/protobuf/lib/x64/libprotobufd.lib \
                        $${THIRD_PARTY_DIR}/tolua++/lib/x64/tolua++D.lib \
                        $${THIRD_PARTY_DIR}/lua/lib/x64/lua5.1.lib
        }
    } else {
        message("32-bit")
        CONFIG(release,debug|release){
            ZSS_LIBS += $${THIRD_PARTY_DIR}/protobuf/lib/x86/libprotobuf.lib \
                        $${THIRD_PARTY_DIR}/tolua++/lib/x86/tolua++.lib \
                        $${THIRD_PARTY_DIR}/lua/lib/x86/lua5.1.lib
        }
        CONFIG(debug,debug|release){
            ZSS_LIBS += $${THIRD_PARTY_DIR}/protobuf/lib/x86/libprotobufd.lib \
                        $${THIRD_PARTY_DIR}/tolua++/lib/x86/tolua++.lib \
                        $${THIRD_PARTY_DIR}/lua/lib/x86/lua5.1.lib
        }
    }

    ZSS_INCLUDES += \
        $${THIRD_PARTY_DIR}/protobuf/include \
        $${THIRD_PARTY_DIR}/Eigen \

}

unix:!macx{
    ZSS_INCLUDES += \
        /usr/include/eigen3 \
        /usr/local/include
    ZSS_LIBS += \
        -llua5.1 \
        -ldl \
        -ltolua++5.1 \
        -lprotobuf
}

INCLUDEPATH += \
    $$ZSS_INCLUDES

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += \
    $$ZSS_LIBS \
    -L"/usr/local/lib" \
    -L"/usr/local/cuda/lib64" \
    -lcudart -lcufft \
    -L"/usr/lib/gcc/x86_64-linux-gnu/7" \

CUDA_SOURCES += src/ssl/cudatest.cu

CUDA_SDK = "/usr/local/cuda/"
CUDA_DIR = "/usr/local/cuda/"
SYSTEM_NAME = ubuntu
SYSTEM_TYPE = 64
CUDA_ARCH = compute_86
NVCC_OPTIONS = --use_fast_math
INCLUDEPATH += $$CUDA_DIR/include
QMAKE_LIBDIR += $$CUDA_DIR/lib64/
CUDA_OBJECTS_DIR = ./

CUDA_LIBS = cudart cufft
CUDA_INC = $$join(INCLUDEPATH, '" -I"', '-I"', '"')
NVCC_LIBS = $$join(CUDA_LIBS, ' -l', '-l', '')

CONFIG(debug, debug|release) {
cuda_d.input = CUDA_SOURCES
cuda_d.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
cuda_d.commands = $$CUDA_DIR/bin/nvcc -D_DEBUG $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
cuda_d.dependency_type = TYPE_C
QMAKE_EXTRA_COMPILERS += cuda_d
}
else {
cuda.input = CUDA_SOURCES
cuda.output = $$CUDA_OBJECTS_DIR/${QMAKE_FILE_BASE}_cuda.o
cuda.commands = $$CUDA_DIR/bin/nvcc $$NVCC_OPTIONS $$CUDA_INC $$NVCC_LIBS --machine $$SYSTEM_TYPE -arch=$$CUDA_ARCH -O3 -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
cuda.dependency_type = TYPE_C
QMAKE_EXTRA_COMPILERS += cuda
}


DEPENDPATH += .

DISTFILES += \
    cudatest.cu

INCLUDEPATH += \
    share \
    share/proto/cpp \
    src \
    src/ssl \
    src/LuaModule \
    src/ssl/bayes \
    src/ssl/cornell \
    src/ssl/defence \
    src/ssl/MotionControl \
    src/ssl/PathPlan \
    src/ssl/PointCalculation \
    src/ssl/rolematch \
    src/ssl/skill \
    src/ssl/Vision \
    src/ssl/WorldModel \

SOURCES += \
    share/parammanager.cpp \
    share/proto/cpp/grSim_Commands.pb.cc \
    share/proto/cpp/grSimMessage.pb.cc \
    share/proto/cpp/grSim_Packet.pb.cc \
    share/proto/cpp/grSim_Replacement.pb.cc \
    share/proto/cpp/log_labeler_data.pb.cc \
    share/proto/cpp/log_labels.pb.cc \
    share/proto/cpp/src_cmd.pb.cc \
    share/proto/cpp/referee.pb.cc \
    share/proto/cpp/src_rawvision.pb.cc \
    share/proto/cpp/src_heatMap.pb.cc \
    share/proto/cpp/messages_robocup_ssl_detection.pb.cc \
    share/proto/cpp/messages_robocup_ssl_geometry_legacy.pb.cc \
    share/proto/cpp/messages_robocup_ssl_geometry.pb.cc \
    share/proto/cpp/messages_robocup_ssl_refbox_log.pb.cc \
    share/proto/cpp/messages_robocup_ssl_wrapper_legacy.pb.cc \
    share/proto/cpp/messages_robocup_ssl_wrapper.pb.cc \
    share/proto/cpp/ssl_game_controller_auto_ref.pb.cc \
    share/proto/cpp/ssl_game_controller_common.pb.cc \
    share/proto/cpp/ssl_game_controller_team.pb.cc \
    share/proto/cpp/ssl_game_event_2019.pb.cc \
    share/proto/cpp/ssl_game_event.pb.cc \
    share/proto/cpp/ssl_referee.pb.cc \
    share/proto/cpp/vision_detection.pb.cc \
    share/proto/cpp/zss_cmd.pb.cc \
    share/proto/cpp/zss_debug.pb.cc \
    src/LuaModule/LuaModule.cpp \
    src/LuaModule/lua_zeus.cpp \
    src/ssl/bayes/BayesFilter.cpp \
    src/ssl/bayes/BayesParam.cpp \
    src/ssl/bayes/BayesReader.cpp \
    src/ssl/bayes/MatchState.cpp \
    src/ssl/cornell/Trajectory.cpp \
    src/ssl/cornell/TrajectoryStructs.cpp \
    src/ssl/cornell/TrajectorySupport.cpp \
    src/ssl/defence/AttributeSet.cpp \
    src/ssl/defence/DefenceInfo.cpp \
    src/ssl/defence/EnemyDefendTacticAnalys.cpp \
    src/ssl/defence/EnemyDefendTacticArea.cpp \
    src/ssl/defence/EnemySituation.cpp \
    src/ssl/defence/OppAttributesFactory.cpp \
    src/ssl/defence/OppPlayer.cpp \
    src/ssl/defence/OppRoleFactory.cpp \
    src/ssl/defence/OppRoleMatcher.cpp \
    src/ssl/defence/Trigger.cpp \
    src/ssl/MotionControl/CMmotion.cpp \
    src/ssl/MotionControl/ControlModel.cpp \
    src/ssl/MotionControl/CubicEquation.cpp \
    src/ssl/MotionControl/DynamicsSafetySearch.cpp \
    src/ssl/MotionControl/QuadraticEquation.cpp \
    src/ssl/MotionControl/QuarticEquation.cpp \
    src/ssl/PathPlan/KDTreeNew.cpp \
    src/ssl/PathPlan/ObstacleNew.cpp \
    src/ssl/PathPlan/PredictTrajectory.cpp \
    src/ssl/PathPlan/RRTPathPlannerNew.cpp \
    src/ssl/PointCalculation/AssistPoint.cpp \
    src/ssl/PointCalculation/AtomPos.cpp \
    src/ssl/PointCalculation/ChipBallJudge.cpp \
    src/ssl/PointCalculation/CornerAreaPos.cpp \
    src/ssl/PointCalculation/DefaultPos.cpp \
    src/ssl/PointCalculation/DefendDribble.cpp \
    src/ssl/PointCalculation/DefPos1G2D.cpp \
    src/ssl/PointCalculation/DefPos2013.cpp \
    src/ssl/PointCalculation/DefPos2015.cpp \
    src/ssl/PointCalculation/GoaliePosV1.cpp \
    src/ssl/PointCalculation/GuardPos.cpp \
    src/ssl/PointCalculation/IndirectDefender.cpp \
    src/ssl/PointCalculation/KickOffDefPosV2.cpp \
    src/ssl/PointCalculation/MarkingPosV2.cpp \
    src/ssl/PointCalculation/MarkingTouchPos.cpp \
    src/ssl/PointCalculation/MiddleAreaPos.cpp \
    src/ssl/PointCalculation/SupportPos.cpp \
    src/ssl/PointCalculation/SupportPos2022.cpp \
    src/ssl/PointCalculation/TandemPos.cpp \
    src/ssl/PointCalculation/TouchKickPos.cpp \
    src/ssl/PointCalculation/WaitKickPos.cpp \
    src/ssl/rolematch/munkres.cpp \
    src/ssl/rolematch/munkresTacticPositionMatcher.cpp \
    src/ssl/skill/Advance.cpp \
    src/ssl/skill/AdvanceBallV1.cpp \
    src/ssl/skill/AdvanceBallV2.cpp \
    src/ssl/skill/AdvanceBallV3.cpp \
    src/ssl/skill/AdvanceBallV4.cpp \
    src/ssl/skill/Break.cpp \
    src/ssl/skill/ChaseKickV1.cpp \
    src/ssl/skill/ChaseKickV2.cpp \
    src/ssl/skill/CircleAndPass.cpp \
    src/ssl/skill/CrazyPush.cpp \
    src/ssl/skill/DribbleTurn.cpp \
    src/ssl/skill/DribbleTurnKick.cpp \
    src/ssl/skill/DriftKick.cpp \
    src/ssl/skill/Factory.cpp \
    src/ssl/skill/FetchBall.cpp \
    src/ssl/skill/ForceStartRush.cpp \
    src/ssl/skill/GetBallV3.cpp \
    src/ssl/skill/GoTechChalPos.cpp \
    src/ssl/skill/Goalie2013.cpp \
    src/ssl/skill/Goalie2022.cpp \
    src/ssl/skill/GoAndTurn.cpp \
    src/ssl/skill/GoAndTurnKick.cpp \
    src/ssl/skill/GoAndTurnKickV3.cpp \
    src/ssl/skill/GoAndTurnKickV4.cpp \
    src/ssl/skill/GoAroundRobot.cpp \
    src/ssl/skill/GoSupport.cpp \
    src/ssl/skill/GotoPosition.cpp \
    src/ssl/skill/InterceptBall.cpp \
    src/ssl/skill/InterceptBallV2.cpp \
    src/ssl/skill/InterceptBallV3.cpp \
    src/ssl/skill/InterceptBallV4.cpp \
    src/ssl/skill/Marking.cpp \
    src/ssl/skill/MarkingFront.cpp \
    src/ssl/skill/MarkingTouch.cpp \
    src/ssl/skill/OpenSpeed.cpp \
    src/ssl/skill/PassBall.cpp \
    src/ssl/skill/PenaltyDefV1.cpp \
    src/ssl/skill/PenaltyDefV2.cpp \
    src/ssl/skill/PenaltyGoalie2012.cpp \
    src/ssl/skill/PenaltyKick2013.cpp \
    src/ssl/skill/PenaltyKick2014.cpp \
    src/ssl/skill/PenaltyKickV2.cpp \
    src/ssl/skill/PlayerTask.cpp \
    src/ssl/skill/ProtectBall.cpp \
    src/ssl/skill/ReceivePass.cpp \
    src/ssl/skill/ShootBall.cpp \
    src/ssl/skill/ShootBallV2.cpp \
    src/ssl/skill/ShootoutGoalie.cpp \
    src/ssl/skill/ShootoutGoalieV2.cpp \
    src/ssl/skill/SlowGetBall.cpp \
    src/ssl/skill/SmartGotoPosition.cpp \
    src/ssl/skill/Speed.cpp \
    src/ssl/skill/StopRobot.cpp \
    src/ssl/skill/Tandem.cpp \
    src/ssl/skill/TestCircleBall.cpp \
    src/ssl/skill/TimeDelayTest.cpp \
    src/ssl/skill/TouchKick.cpp \
    src/ssl/skill/WaitTouch.cpp \
    src/ssl/Vision/BallPredictor.cpp \
    src/ssl/Vision/DataReceiver4rbk.cpp \
    src/ssl/Vision/RobotPredictor.cpp \
    src/ssl/Vision/VisionModule.cpp \
    src/ssl/WorldModel/GetLuaData.cpp \
    src/ssl/WorldModel/RobotCapability.cpp \
    src/ssl/WorldModel/WorldModel_basic.cpp \
    src/ssl/WorldModel/WorldModel_enemy.cpp \
    src/ssl/WorldModel/WorldModel_lua.cpp \
    src/ssl/WorldModel/WorldModel_utils.cpp \
    src/ssl/ActionModule.cpp \
    src/ssl/BallSpeedModel.cpp \
    src/ssl/BallStatus.cpp \
    src/ssl/BestPlayer.cpp \
    src/ssl/BufferCounter.cpp \
    src/ssl/Compensate.cpp \
    src/ssl/ContactChecker.cpp \
    src/ssl/CtrlBreakHandler.cpp \
    src/ssl/DecisionModule.cpp \
    src/ssl/DefendUtils.cpp \
    src/ssl/FilteredObject.cpp \
    src/ssl/FreeKickUtils.cpp \
    src/ssl/GDebugEngine.cpp \
    src/ssl/Global.cpp \
    src/ssl/geometry.cpp \
    src/ssl/gpuBestAlgThread.cpp \
    src/ssl/KickDirection.cpp \
    src/ssl/matrix2d.cpp \
    src/ssl/NormalPlayUtils.cpp \
    src/ssl/OptionModule.cpp \
    src/ssl/ParamManagerNew.cpp \
    src/ssl/PassRangeList.cpp \
    src/ssl/PenaltyPosCleaner.cpp \
    src/ssl/PlayerCommandV2.cpp \
    src/ssl/RobotSensor.cpp \
    src/ssl/ShootRangeList.cpp \
    src/ssl/utils.cpp \
    src/SSLStrategy.cpp \

HEADERS += \
    share/dataqueue.hpp \
    share/parammanager.h \
    share/proto/cpp/grSim_Commands.pb.h \
    share/proto/cpp/grSimMessage.pb.h \
    share/proto/cpp/grSim_Packet.pb.h \
    share/proto/cpp/grSim_Replacement.pb.h \
    share/proto/cpp/log_labeler_data.pb.h \
    share/proto/cpp/log_labels.pb.h \
    share/proto/cpp/src_cmd.pb.h \
    share/proto/cpp/referee.pb.h \
    share/proto/cpp/src_rawvision.pb.h \
    share/proto/cpp/src_heatMap.pb.h \
    share/proto/cpp/messages_robocup_ssl_detection.pb.h \
    share/proto/cpp/messages_robocup_ssl_geometry_legacy.pb.h \
    share/proto/cpp/messages_robocup_ssl_geometry.pb.h \
    share/proto/cpp/messages_robocup_ssl_refbox_log.pb.h \
    share/proto/cpp/messages_robocup_ssl_wrapper_legacy.pb.h \
    share/proto/cpp/messages_robocup_ssl_wrapper.pb.h \
    share/proto/cpp/ssl_game_controller_auto_ref.pb.h \
    share/proto/cpp/ssl_game_controller_common.pb.h \
    share/proto/cpp/ssl_game_controller_team.pb.h \
    share/proto/cpp/ssl_game_event_2019.pb.h \
    share/proto/cpp/ssl_game_event.pb.h \
    share/proto/cpp/ssl_referee.pb.h \
    share/proto/cpp/vision_detection.pb.h \
    share/proto/cpp/zss_cmd.pb.h \
    share/proto/cpp/zss_debug.pb.h \
    share/singleton.hpp \
    share/staticparams.h \
    src/LuaModule/lauxlib.h \
    src/LuaModule/luaconf.h \
    src/LuaModule/lua.h \
    src/LuaModule/lualib.h \
    src/LuaModule/LuaModule.h \
    src/LuaModule/tolua++.h \
    src/ssl/bayes/BayesFilter.h \
    src/ssl/bayes/BayesParam.h \
    src/ssl/bayes/BayesReader.h \
    src/ssl/bayes/MatchState.h \
    src/ssl/cornell/Trajectory.h \
    src/ssl/cornell/TrajectoryStructs.h \
    src/ssl/cornell/TrajectorySupport.h \
    src/ssl/defence/Attribute.h \
    src/ssl/defence/AttributeSet.h \
    src/ssl/defence/DefenceInfo.h \
    src/ssl/defence/EnemyDefendTacticAnalys.h \
    src/ssl/defence/EnemyDefendTacticArea.h \
    src/ssl/defence/EnemySituation.h \
    src/ssl/defence/OppAttributesFactory.h \
    src/ssl/defence/OppPlayer.h \
    src/ssl/defence/OppRole.h \
    src/ssl/defence/OppRoleFactory.h \
    src/ssl/defence/OppRoleMatcher.h \
    src/ssl/defence/Trigger.h \
    src/ssl/MotionControl/CMmotion.h \
    src/ssl/MotionControl/ControlModel.h \
    src/ssl/MotionControl/CubicEquation.h \
    src/ssl/MotionControl/DynamicsSafetySearch.h \
    src/ssl/MotionControl/QuadraticEquation.h \
    src/ssl/MotionControl/QuarticEquation.h \
    src/ssl/MotionControl/util.h \
    src/ssl/MotionControl/vector.h \
    src/ssl/PathPlan/FastAllocator.h \
    src/ssl/PathPlan/KDTreeNew.h \
    src/ssl/PathPlan/ObstacleNew.h \
    src/ssl/PathPlan/PredictTrajectory.h \
    src/ssl/PathPlan/RRTPathPlannerNew.h \
    src/ssl/PointCalculation/AssistPoint.h \
    src/ssl/PointCalculation/AtomPos.h \
    src/ssl/PointCalculation/ChipBallJudge.h \
    src/ssl/PointCalculation/CornerAreaPos.h \
    src/ssl/PointCalculation/DefaultPos.h \
    src/ssl/PointCalculation/DefendDribble.h \
    src/ssl/PointCalculation/DefPos1G2D.h \
    src/ssl/PointCalculation/DefPos2013.h \
    src/ssl/PointCalculation/DefPos2015.h \
    src/ssl/PointCalculation/GoaliePosV1.h \
    src/ssl/PointCalculation/GuardPos.h \
    src/ssl/PointCalculation/IndirectDefender.h \
    src/ssl/PointCalculation/KickOffDefPosV2.h \
    src/ssl/PointCalculation/MarkingPosV2.h \
    src/ssl/PointCalculation/MarkingTouchPos.h \
    src/ssl/PointCalculation/SupportPos.h \
    src/ssl/PointCalculation/SupportPos2022.h \
    src/ssl/PointCalculation/TandemPos.h \
    src/ssl/PointCalculation/TouchKickPos.h \
    src/ssl/PointCalculation/WaitKickPos.h \
    src/ssl/rolematch/matrix.h \
    src/ssl/rolematch/munkres.h \
    src/ssl/rolematch/munkresTacticPositionMatcher.h \
    src/ssl/skill/Advance.h \
    src/ssl/skill/AdvanceBallV1.h \
    src/ssl/skill/AdvanceBallV2.h \
    src/ssl/skill/AdvanceBallV3.h \
    src/ssl/skill/AdvanceBallV4.h \
    src/ssl/skill/break.h \
    src/ssl/skill/ChaseKickV1.h \
    src/ssl/skill/ChaseKickV2.h \
    src/ssl/skill/CircleAndPass.h \
    src/ssl/skill/CrazyPush.h \
    src/ssl/skill/DribbleTurn.h \
    src/ssl/skill/DribbleTurnKick.h \
    src/ssl/skill/DriftKick.h \
    src/ssl/skill/Factory.h \
    src/ssl/skill/FetchBall.h \
    src/ssl/skill/ForceStartRush.h \
    src/ssl/skill/GetBallV3.h \
    src/ssl/skill/Goalie2013.h \
    src/ssl/skill/Goalie2022.h \
    src/ssl/skill/GoAndTurn.h \
    src/ssl/skill/GoAndTurnKick.h \
    src/ssl/skill/GoAndTurnKickV3.h \
    src/ssl/skill/GoAndTurnKickV4.h \
    src/ssl/skill/GoAroundRobot.h \
    src/ssl/skill/GoSupport.h \
    src/ssl/skill/GotoPosition.h \
    src/ssl/skill/InterceptBall.h \
    src/ssl/skill/InterceptBallV2.h \
    src/ssl/skill/InterceptBallV3.h \
    src/ssl/skill/InterceptBallV4.h \
    src/ssl/skill/Marking.h \
    src/ssl/skill/MarkingFront.h \
    src/ssl/skill/MarkingTouch.h \
    src/ssl/skill/OpenSpeed.h \
    src/ssl/skill/PassBall.h \
    src/ssl/skill/PenaltyDefV1.h \
    src/ssl/skill/PenaltyDefV2.h \
    src/ssl/skill/PenaltyGoalie2012.h \
    src/ssl/skill/PenaltyKick2013.h \
    src/ssl/skill/PenaltyKick2014.h \
    src/ssl/skill/PenaltyKickV2.h \
    src/ssl/skill/PlayerTask.h \
    src/ssl/skill/ProtectBall.h \
    src/ssl/skill/ReceivePass.h \
    src/ssl/skill/ShootBall.h \
    src/ssl/skill/ShootBallV2.h \
    src/ssl/skill/ShootoutGoalie.h \
    src/ssl/skill/shootoutGoalieV2.h \
    src/ssl/skill/SlowGetBall.h \
    src/ssl/skill/SmartGotoPosition.h \
    src/ssl/skill/Speed.h \
    src/ssl/skill/StopRobot.h \
    src/ssl/skill/Tandem.h \
    src/ssl/skill/TestCircleBall.h \
    src/ssl/skill/TimeDelayTest.h \
    src/ssl/skill/TouchKick.h \
    src/ssl/skill/WaitTouch.h \
    src/ssl/skill/GoTechChalPos.h \
    src/ssl/Vision/BallPredictor.h \
    src/ssl/Vision/DataReceiver4rbk.h \
    src/ssl/Vision/RobotPredictor.h \
    src/ssl/Vision/VisionModule.h \
    src/ssl/WorldModel/DribbleStatus.h \
    src/ssl/WorldModel/GetLuaData.h \
    src/ssl/WorldModel/KickStatus.h \
    src/ssl/WorldModel/RobotCapability.h \
    src/ssl/WorldModel/robot_power.h \
    src/ssl/WorldModel/server.h \
    src/ssl/WorldModel/WorldDefine.h \
    src/ssl/WorldModel/WorldModel.h \
    src/ssl/ActionModule.h \
    src/ssl/BallSpeedModel.h \
    src/ssl/BallStatus.h \
    src/ssl/BestPlayer.h \
    src/ssl/BufferCounter.h \
    src/ssl/ClassFactory.h \
    src/ssl/CommandFactory.h \
    src/ssl/Compensate.h \
    src/ssl/ContactChecker.h \
    src/ssl/CtrlBreakHandler.h \
    src/ssl/DecisionModule.h \
    src/ssl/DefendUtils.h \
    src/ssl/FilteredObject.h \
    src/ssl/FreeKickUtils.h \
    src/ssl/game_state.h \
    src/ssl/GDebugEngine.h \
    src/ssl/Global.h \
    src/ssl/geometry.h \
    src/ssl/gpuBestAlgThread.h \
    src/ssl/IEvaluator.h \
    src/ssl/KickDirection.h \
    src/ssl/matrix2d.h \
    src/ssl/misc_types.h \
    src/ssl/net_gui.h \
    src/ssl/NormalPlayUtils.h \
    src/ssl/OptionModule.h \
    src/ssl/os_param.h \
    src/ssl/param.h \
    src/ssl/ParamManagerNew.h \
    src/ssl/PassRangeList.h \
    src/ssl/PenaltyPosCleaner.h \
    src/ssl/PlayerCommand.h \
    src/ssl/PlayerCommandV2.h \
    src/ssl/playmode.h \
    src/ssl/referee_commands.h \
    src/ssl/RobotSensor.h \
    src/ssl/ShootRangeList.h \
    src/ssl/singleton.h \
    src/ssl/TaskMediator.h \
    src/ssl/utils.h \
    src/ssl/ValueRange.h \

win32-msvc*: QMAKE_LFLAGS += /FORCE:MULTIPLE

QMAKE_CXXFLAGS += -utf-8
unix:!macx{
    QMAKE_CXXFLAGS += -Wno-comment -Wno-reorder -Wno-conversion-null
}

#message($$INCLUDEPATH)

#LD_LIBRARY_PATH=dir：$LD_LIBRARY_PATH
#export LD_LIBRARY_PATH
