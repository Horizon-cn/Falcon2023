
set(THIRDPARTY_LIB_DIR ${CMAKE_SOURCE_DIR}/3rdParty)

## protobuf
find_package(Protobuf REQUIRED)

## lua
find_package(Lua REQUIRED)

## tolua++
find_package(toluapp REQUIRED)

## zlib
find_package(ZLIB)

## ode
find_package(ODE REQUIRED)

## QT
find_package(Qt5 COMPONENTS Core Quick SerialPort Widgets Network Gui Qml Quick REQUIRED)

## OpenGL
find_package(OpenGL REQUIRED)

## Eigen
# find_package(Eigen3 REQUIRED)
