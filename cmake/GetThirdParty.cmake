set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
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

# VarTypes
find_package(VarTypes)

## QT
IF(WIN32)
	## if you have different Qt visions and CMake cannot link the right one, you can manually set the correct path or use the environment variable
    option(USE_ENV_FINDQT OFF)
    option(CUSTOM_PATH_FINDQT OFF)
    
    if (USE_ENV_FINDQT)
        set(CMAKE_PREFIX_PATH $ENV{QT_CMAKE})
        message("USE_ENV_FINDQT : $ENV{QT_CMAKE}")
    elseif (CUSTOM_PATH_FINDQT)
        set(CUSTOM_PATH_QT "D:/QT/5.15.2/msvc2019_64/lib/cmake/Qt5")
        set(CMAKE_PREFIX_PATH ${CUSTOM_PATH_QT})
        message("CUSTOM_PATH_FINDQT : ${CUSTOM_PATH_QT}")
    endif()
ENDIF()
find_package(Qt5 COMPONENTS Core Quick QuickControls2 SerialPort Widgets Network Gui Qml OpenGL Gamepad REQUIRED)

## KDDockWidgets
include(${CMAKE_SOURCE_DIR}/cmake/GetKDDockWidgets.cmake)

## boost
# include(${CMAKE_SOURCE_DIR}/cmake/GetBoost.cmake)

## OpenGL
find_package(OpenGL REQUIRED)

## Eigen
include(${CMAKE_SOURCE_DIR}/cmake/GetEigen.cmake)
