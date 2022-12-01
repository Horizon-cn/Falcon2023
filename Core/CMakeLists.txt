set(TARGET_NAME Core)
set(libs)
set(incs)
# Core - Medusa
## Protobuf
find_package(Protobuf REQUIRED)
list(APPEND incs ${PROTOBUF_INCLUDE_DIR})
list(APPEND libs ${PROTOBUF_LIBRARIES})
## Qt5
find_package(Qt5 COMPONENTS Core Qml Quick Network REQUIRED)
list(APPEND libs Qt5::Core Qt5::Qml Qt5::Quick Qt5::Network)
## Lua
find_package(Lua REQUIRED)
list(APPEND incs ${LUA_INCLUDE_DIR})
list(APPEND libs ${LUA_LIBRARIES})
## tolua++
find_package(toluapp REQUIRED)
list(APPEND incs ${TOLUAPP_INCLUDE_DIR})
list(APPEND libs ${TOLUAPP_LIBRARIES})
# EXECUTE_PROCESS(
#    COMMAND ${TOLUAPP_EXECUTABLE} -n zeus -o ${CMAKE_CURRENT_SOURCE_DIR}/src/LuaModule/lua_zeus.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/LuaModule/zeus.pkg
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/LuaModule
# )
## Eigen
# find_package(Eigen3 REQUIRED)
# list(APPEND incs ${EIGEN3_INCLUDE_DIR})


set(PROTO_LIST
    game_event
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
file(GLOB PROJECT_SOURCE
    "${CMAKE_SOURCE_DIR}/share/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SSLStrategy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/LuaModule/LuaModule.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/bayes/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/cornell/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/defence/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/MotionControl/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/PathPlan/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/PointCalculation/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/rolematch/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/skill/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/Vision/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ssl/WorldModel/*.cpp"
    ${PROTO_H}
    ${PROTO_CPP}
    "${CMAKE_CURRENT_SOURCE_DIR}/src/LuaModule/lua_zeus.cpp"
)
add_executable(${TARGET_NAME} ${PROJECT_SOURCE})
target_link_libraries(${TARGET_NAME} PRIVATE ${libs})

# copy lua dll to ZBin
IF(WIN32)
set(thirdParty ${CMAKE_CURRENT_SOURCE_DIR}/../3rdParty)
file(COPY ${thirdParty}/lua/bin/lua5.1.dll DESTINATION ${CMAKE_SOURCE_DIR}/ZBin/)
ENDIF()