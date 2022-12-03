
set(THIRDPARTY_LIB_DIR ${CMAKE_SOURCE_DIR}/3rdParty)

## protobuf
include(${CMAKE_SOURCE_DIR}/cmake/GetProtobuf.cmake)

## lua
include(${CMAKE_SOURCE_DIR}/cmake/GetLua.cmake)

## tolua++
find_package(toluapp REQUIRED)

## zlib
include(${CMAKE_SOURCE_DIR}/cmake/GetZLIB.cmake)

## ode
find_package(ODE REQUIRED)

## QT
find_package(Qt5 COMPONENTS Core Quick SerialPort Widgets Network Gui Qml Quick REQUIRED)

## OpenGL
find_package(OpenGL REQUIRED)

## Eigen
# find_package(Eigen3 REQUIRED)
