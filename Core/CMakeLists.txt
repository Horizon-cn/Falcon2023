set(TARGET_NAME Core)
set(libs)
set(incs)
# Core - Medusa
## Protobuf
list(APPEND incs ${Protobuf_INCLUDE_DIR})
list(APPEND libs ${Protobuf_LIBRARY_RELEASE} ${Protobuf_LITE_LIBRARY_RELEASE} ${Protobuf_PROTOC_LIBRARY_RELEASE})
## Qt5
list(APPEND libs Qt5::Core Qt5::Qml Qt5::Quick Qt5::Network Qt5::Widgets)
## Lua
list(APPEND incs ${LUA_INCLUDE_DIR})
list(APPEND libs ${LUA_LIBRARIES})
## tolua++
list(APPEND incs ${TOLUAPP_INCLUDE_DIR})
list(APPEND libs ${TOLUAPP_LIBRARIES})
# EXECUTE_PROCESS(
#    COMMAND ${TOLUAPP_EXECUTABLE} -n zeus -o ${CMAKE_CURRENT_SOURCE_DIR}/src/LuaModule/lua_zeus.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/LuaModule/zeus.pkg
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/LuaModule
# )
## Eigen
# list(APPEND incs ${EIGEN3_INCLUDE_DIR})

set(PROTO_LIST
    grSim_Commands
    grSimMessage
    grSim_Packet
    grSim_Replacement
    messages_robocup_ssl_detection
    messages_robocup_ssl_geometry_legacy
    messages_robocup_ssl_geometry
    messages_robocup_ssl_refbox_log
    messages_robocup_ssl_wrapper_legacy
    messages_robocup_ssl_wrapper
    ssl_referee
    ssl_game_event
    ssl_game_event_2019
    ssl_game_controller_common
    vision_detection
    zss_cmd
    zss_debug
    src_cmd
    src_heatMap
)
get_pb_file(PROTO_H PROTO_CPP ${PROTO_LIST})

set(PROJECT_INCLUDE_DIRS
    ${incs}
    ${CMAKE_BINARY_DIR}/proto
    ${CMAKE_SOURCE_DIR}/share
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ssl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/LuaModule
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/bayes
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/cornell
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/defence
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/MotionControl
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/PathPlan
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/PointCalculation
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/rolematch
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/skill
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/Vision
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/WorldModel
)
include_directories(${PROJECT_INCLUDE_DIRS})

file(GLOB HEADERS "./src/*.h")
file (GLOB LUAMODULE_HEADERS "./src/LuaModule/*.h")
file (GLOB SSL_HEADERS "./src/ssl/*.h")
file (GLOB SSL_BAYES_HEADERS "./src/ssl/bayes/*.h")
file (GLOB SSL_CMU_HEADERS "./src/ssl/cmu/*.h")
file (GLOB SSL_CORNELL_HEADERS "./src/ssl/cornell/*.h")
file (GLOB SSL_DEFENCE_HEADERS "./src/ssl/defence/*.h")
file (GLOB SSL_ROLEMATCH_HEADERS "./src/ssl/rolematch/*.h")
file (GLOB SSL_SKILL_HEADERS "./src/ssl/skill/*.h")
file (GLOB SSL_PATHPLAN_HEADERS "./src/ssl/PathPlan/*.h")
file (GLOB SSL_MOTIONCONTROL_HEADERS "./src/ssl/MotionControl/*.h")
file (GLOB SSL_POINTCALCULATION_HEADERS "./src/ssl/PointCalculation/*.h")
file (GLOB SSL_VISION_HEADERS "./src/ssl/Vision/*.h")
file (GLOB SSL_WORLDMODEL_HEADERS "./src/ssl/WorldModel/*.h")
file (GLOB SHARE_HEADERS "${CMAKE_SOURCE_DIR}/share/*.h")
aux_source_directory(./src DIR_SRCS)
aux_source_directory(./src/LuaModule DIR_LUAMODULE_SRCS)
aux_source_directory(./src/ssl DIR_SSL_SRCS)
aux_source_directory(./src/ssl/bayes DIR_SSL_BAYES_SRCS)
aux_source_directory(./src/ssl/cornell DIR_SSL_CORNELL_SRCS)
aux_source_directory(./src/ssl/defence DIR_SSL_DEFENCE_SRCS)
aux_source_directory(./src/ssl/rolematch DIR_SSL_ROLEMATCH_SRCS)
aux_source_directory(./src/ssl/skill DIR_SSL_SKILL_SRCS)
aux_source_directory(./src/ssl/PathPlan DIR_SSL_PATHPLAN_SRCS)
aux_source_directory(./src/ssl/MotionControl DIR_SSL_MOTIONCONTROL_SRCS)
aux_source_directory(./src/ssl/PointCalculation DIR_SSL_POINTCALCULATION_SRCS)
aux_source_directory(./src/ssl/Vision DIR_SSL_VISION_SRCS)
aux_source_directory(./src/ssl/WorldModel DIR_SSL_WORLDMODEL_SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/share DIR_SHARE_SRCS)
# for VS solution file
IF(WIN32)
source_group("include" FILES ${HEADERS})
source_group("src" FILES ${DIR_SRCS})
source_group("include\\LuaModule" FILES ${LUAMODULE_HEADERS})
source_group("src\\LuaModule" FILES ${DIR_LUAMODULE_SRCS})
source_group("include\\ssl" FILES ${SSL_HEADERS})
source_group("src\\ssl" FILES ${DIR_SSL_SRCS})
source_group("include\\ssl\\bayes" FILES ${SSL_BAYES_HEADERS})
source_group("src\\ssl\\bayes" FILES ${DIR_SSL_BAYES_SRCS})
source_group("include\\ssl\\cmu" FILES ${SSL_CMU_HEADERS})
source_group("include\\ssl\\cornell" FILES ${SSL_CORNELL_HEADERS})
source_group("src\\ssl\\cornell" FILES ${DIR_SSL_CORNELL_SRCS})
source_group("include\\ssl\\defence" FILES ${SSL_DEFENCE_HEADERS})
source_group("src\\ssl\\defence" FILES ${DIR_SSL_DEFENCE_SRCS})
source_group("include\\ssl\\rolematch" FILES ${SSL_ROLEMATCH_HEADERS})
source_group("src\\ssl\\rolematch" FILES ${DIR_SSL_ROLEMATCH_SRCS})
source_group("include\\ssl\\skill" FILES ${SSL_SKILL_HEADERS})
source_group("src\\ssl\\skill" FILES ${DIR_SSL_SKILL_SRCS})
source_group("include\\ssl\\PathPlan" FILES ${SSL_PATHPLAN_HEADERS})
source_group("src\\ssl\\PathPlan" FILES ${DIR_SSL_PATHPLAN_SRCS})
source_group("include\\ssl\\MotionControl" FILES ${SSL_MOTIONCONTROL_HEADERS})
source_group("src\\ssl\\MotionControl" FILES ${DIR_SSL_MOTIONCONTROL_SRCS})
source_group("include\\ssl\\PointCalculation" FILES ${SSL_POINTCALCULATION_HEADERS})
source_group("src\\ssl\\PointCalculation" FILES ${DIR_SSL_POINTCALCULATION_SRCS})
source_group("include\\ssl\\Vision" FILES ${SSL_VISION_HEADERS})
source_group("src\\ssl\\Vision" FILES ${DIR_SSL_VISION_SRCS})
source_group("include\\ssl\\WorldModel" FILES ${SSL_WORLDMODEL_HEADERS})
source_group("src\\ssl\\WorldModel" FILES ${DIR_SSL_WORLDMODEL_SRCS})
source_group("include\\share" FILES ${SHARE_HEADERS})
source_group("src\\share" FILES ${DIR_SHARE_SRCS})
ENDIF()
add_executable(${TARGET_NAME} 
		${PROTO_H} 
		${PROTO_CPP}
		${DIR_SRCS}
		${DIR_LUAMODULE_SRCS}
		${DIR_SSL_SRCS}
		${DIR_SSL_BAYES_SRCS}
		${DIR_SSL_CORNELL_SRCS}
		${DIR_SSL_DEFENCE_SRCS}
		${DIR_SSL_ROLEMATCH_SRCS}
		${DIR_SSL_SKILL_SRCS}
		${DIR_SSL_PATHPLAN_SRCS}
		${DIR_SSL_MOTIONCONTROL_SRCS}
		${DIR_SSL_POINTCALCULATION_SRCS}
		${DIR_SSL_VISION_SRCS}
		${DIR_SSL_WORLDMODEL_SRCS}
		${DIR_SHARE_SRCS}
		${HEADERS}
		${LUAMODULE_HEADERS}
		${SSL_HEADERS}
		${SSL_BAYES_HEADERS}
		${SSL_CMU_HEADERS}
		${SSL_CORNELL_HEADERS}
		${SSL_DEFENCE_HEADERS}
		${SSL_ROLEMATCH_HEADERS}
		${SSL_SKILL_HEADERS}
		${SSL_PATHPLAN_HEADERS}
		${SSL_MOTIONCONTROL_HEADERS}
		${SSL_POINTCALCULATION_HEADERS}
		${SSL_VISION_HEADERS}
		${SSL_WORLDMODEL_HEADERS}
		${SHARE_HEADERS})
target_link_libraries(${TARGET_NAME} PRIVATE ${libs})
