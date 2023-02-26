set(TARGET_NAME Client)

if (WIN32)
    message(${CMAKE_C_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
endif()

if (NOT UNIX AND NOT APPLE)
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
endif()

set(incs)
set(libs)

## find Qt
set(SRC_QT Core Widgets Quick SerialPort Gamepad)
foreach(component ${SRC_QT})
    list(APPEND incs ${Qt5${component}_INCLUDE_DIRS})
    list(APPEND libs Qt5::${component})
endforeach()
if (WIN32)
    list(APPEND libs Qt5::WinMain)
endif()

## find kddockwidgets
IF(WIN32)
    list(APPEND incs ${KDDOCKWIDGETS_INCLUDE_DIRS})
    IF(CMAKE_CONFIGURATION_TYPES STREQUAL "Debug")
        set(KDDOCKWIDGETS_LIBRARIES ${KDDOCKWIDGETS_LIBRARIES_DEBUG})
    ELSE()
        set(KDDOCKWIDGETS_LIBRARIES ${KDDOCKWIDGETS_LIBRARIES_RELEASE})
    ENDIF()        
    list(APPEND libs ${KDDOCKWIDGETS_LIBRARIES})
    message("${KDDOCKWIDGETS_INCLUDE_DIRS} ${KDDOCKWIDGETS_LIBRARIES}")
ELSE()
    list(APPEND libs KDAB::kddockwidgets)
ENDIF()

## find boost
# list(APPEND incs ${Boost_INCLUDE_DIRS})
# list(APPEND libs ${Boost_LIBRARIES})
# message("${Boost_LIBRARIES}")

## Protobuf
list(APPEND incs ${Protobuf_INCLUDE_DIR})
list(APPEND libs ${Protobuf_LIBRARY_RELEASE} ${Protobuf_LITE_LIBRARY_RELEASE} ${Protobuf_PROTOC_LIBRARY_RELEASE})

## Eigen
list(APPEND incs ${EIGEN3_INCLUDE_DIR})

## find Zlib
list(APPEND incs ${ZLIB_INCLUDE_DIRS})
list(APPEND libs ${ZLIB_LIBRARIES})

# project files
## protobuf files
set(PROTO_LIST
    grSim_Commands
    grSimMessage
    grSim_Packet
    grSim_Replacement
    log_labeler_data
    log_labels
    messages_robocup_ssl_detection
    messages_robocup_ssl_geometry_legacy
    messages_robocup_ssl_geometry
    messages_robocup_ssl_refbox_log
    messages_robocup_ssl_wrapper_legacy
    messages_robocup_ssl_wrapper
    messages_robocup_ssl_robot_status
    ssl_game_controller_auto_ref
    ssl_game_controller_common
    ssl_game_controller_team
    ssl_game_event_2019
    ssl_game_event
    ssl_referee
    vision_detection
    zss_cmd
    zss_debug
    zss_rec
    src_heatMap
    src_cmd
    src_option
)
get_pb_file(PROTO_H PROTO_CPP ${PROTO_LIST})

set(QML_DIRS)
list(APPEND QML_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/qml)
set(QML_IMPORT_PATH ${QML_DIRS})
# FILE(GLOB QMLFILES ${QML_DIRS}/*.qml)
FILE(GLOB QML_COMPONENTS_FILES ${QML_DIRS}/Components/*.qml)
FILE(GLOB QML_COMPONENTSKD_FILES ${QML_DIRS}/ComponentsKD/*.qml)
FILE(GLOB QML_GAMEPAD_FILES ${QML_DIRS}/Gamepad/*.qml)
FILE(GLOB QML_KDDOCKWIDGETS_FILES ${QML_DIRS}/KDDockWidgets/*.qml)
FILE(GLOB QML_WIDGETS_FILES ${QML_DIRS}/Widgets/*.qml)

set(PROJECT_INCLUDE_DIRS
    ${CMAKE_BINARY_DIR}/proto
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/comm
    ${CMAKE_CURRENT_SOURCE_DIR}/src/interface
    ${CMAKE_CURRENT_SOURCE_DIR}/src/log
    ${CMAKE_CURRENT_SOURCE_DIR}/src/log/rec_log
    ${CMAKE_CURRENT_SOURCE_DIR}/src/log/worldcup
    ${CMAKE_CURRENT_SOURCE_DIR}/src/other
    ${CMAKE_CURRENT_SOURCE_DIR}/src/referee
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vision
    ${CMAKE_SOURCE_DIR}/share
)
include_directories(${PROJECT_INCLUDE_DIRS} ${incs})

## cpp files
aux_source_directory(./src CPPFILES)
aux_source_directory(./src/comm COMM_CPPFILES)
aux_source_directory(./src/interface INTERFACE_CPPFILES)
aux_source_directory(./src/log LOG_CPPFILES)
aux_source_directory(./src/log/rec_log REC_CPPFILES)
aux_source_directory(./src/log/worldcup WORLDCUP_CPPFILES)
aux_source_directory(./src/other OTHER_CPPFILES)
aux_source_directory(./src/referee REFEREE_CPPFILES)
aux_source_directory(./src/utils UTILS_CPPFILES)
aux_source_directory(./src/vision VISION_CPPFILES)
aux_source_directory(${CMAKE_SOURCE_DIR}/share SHARE_CPPFILES)

## header files
FILE(GLOB HEADERFILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
FILE(GLOB COMM_HEADERFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/comm/*.h)
FILE(GLOB INTERFACE_HEADERFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/interface/*.h)
FILE(GLOB LOG_HEADERFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/log/*.h)
FILE(GLOB REC_HEADERFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/log/rec_log/*.h)
FILE(GLOB WORLDCUP_HEADERFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/log/worldcup/*.h)
FILE(GLOB OTHER_HEADERFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/other/*.h)
FILE(GLOB REFEREE_HEADERFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/referee/*.h)
FILE(GLOB UTILS_HEADERFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.h)
FILE(GLOB VISION_HEADERFILES ${CMAKE_CURRENT_SOURCE_DIR}/src/vision/*.h)
FILE(GLOB SHARE_HEADERFILES ${CMAKE_SOURCE_DIR}/share/*.h)

## rc files
FILE(GLOB RCFILES "${CMAKE_CURRENT_SOURCE_DIR}/*.rc")

## qrc files
FILE(GLOB QRCFILES "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc" "${CMAKE_CURRENT_SOURCE_DIR}/*.conf")

# for VS solution file
IF(WIN32)
source_group("include" FILES ${HEADERFILES})
source_group("include\\comm" FILES ${COMM_HEADERFILES})
source_group("include\\interface" FILES ${INTERFACE_HEADERFILES})
source_group("include\\log" FILES ${LOG_HEADERFILES})
source_group("include\\log\\rec_log" FILES ${REC_HEADERFILES})
source_group("include\\log\\worldcup" FILES ${WORLDCUP_HEADERFILES})
source_group("include\\other" FILES ${OTHER_HEADERFILES})
source_group("include\\referee" FILES ${REFEREE_HEADERFILES})
source_group("include\\utils" FILES ${UTILS_HEADERFILES})
source_group("include\\vision" FILES ${VISION_HEADERFILES})
source_group("include\\share" FILES ${SHARE_HEADERFILES})

source_group("src" FILES ${CPPFILES})
source_group("src\\comm" FILES ${COMM_CPPFILES})
source_group("src\\interface" FILES ${INTERFACE_CPPFILES})
source_group("src\\log" FILES ${LOG_CPPFILES})
source_group("src\\log\\rec_log" FILES ${REC_CPPFILES})
source_group("src\\log\\worldcup" FILES ${WORLDCUP_CPPFILES})
source_group("src\\other" FILES ${OTHER_CPPFILES})
source_group("src\\referee" FILES ${REFEREE_CPPFILES})
source_group("src\\utils" FILES ${UTILS_CPPFILES})
source_group("src\\vision" FILES ${VISION_CPPFILES})
source_group("src\\share" FILES ${SHARE_CPPFILES})

source_group("rc" FILES ${RCFILES})
source_group("qrc" FILES ${QRCFILES})
# source_group("qml" FILES ${QMLFILES})
source_group("qml\\Components" FILES ${QML_COMPONENTS_FILES})
source_group("qml\\ComponentsKD" FILES ${QML_COMPONENTSKD_FILES})
source_group("qml\\Gamepad" FILES ${QML_GAMEPAD_FILES})
source_group("qml\\KDDockWidgets" FILES ${QML_KDDOCKWIDGETS_FILES})
source_group("qml\\Widgets" FILES ${QML_WIDGETS_FILES})
ENDIF()

set(SRC
    ${HEADERFILES}
    ${COMM_HEADERFILES}
    ${INTERFACE_HEADERFILES}
    ${LOG_HEADERFILES}
    ${REC_HEADERFILES}
    ${WORLDCUP_HEADERFILES}
    ${OTHER_HEADERFILES}
    ${REFEREE_HEADERFILES}
    ${UTILS_HEADERFILES}
    ${VISION_HEADERFILES}
    ${SHARE_HEADERFILES}

    ${CPPFILES}
    ${COMM_CPPFILES}
    ${INTERFACE_CPPFILES}
    ${LOG_CPPFILES}
    ${REC_CPPFILES}
    ${WORLDCUP_CPPFILES}
    ${OTHER_CPPFILES}
    ${REFEREE_CPPFILES}
    ${UTILS_CPPFILES}
    ${VISION_CPPFILES}
    ${SHARE_CPPFILES}

    ${RCFILES}
    ${QRCFILES}
    ${QMLFILES}
    ${QML_COMPONENTS_FILES}
    ${QML_COMPONENTSKD_FILES}
    ${QML_GAMEPAD_FILES}
    ${QML_KDDOCKWIDGETS_FILES}
    ${QML_WIDGETS_FILES}
    ${PROTO_CPP}
    ${PROTO_H}
)

add_executable(${TARGET_NAME} ${SRC})
target_compile_definitions(${TARGET_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${TARGET_NAME} PRIVATE ${libs})
