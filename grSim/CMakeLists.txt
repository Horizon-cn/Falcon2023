set(TARGET_NAME grSim)

IF(WIN32)
    message(${CMAKE_C_FLAGS})
ENDIF()

# definitions for knowing the OS from the code
if(MSVC)
    add_definitions(-DHAVE_MSVC)
endif()
if(WIN32)
    add_definitions(-DHAVE_WINDOWS)
endif()
if(UNIX)
    add_definitions(-DHAVE_UNIX)
    if(APPLE)
        add_definitions(-DHAVE_MACOSX)
    else()
        #TODO: fix this, say we have FreeBSD, that's not linux
        add_definitions(-DHAVE_LINUX)
    endif()
endif()

set(incs)
set(libs)

# OpenGL
list(APPEND incs ${OPENGL_INCLUDE_DIR})
list(APPEND libs ${OPENGL_LIBRARIES})

# Qt
# list(APPEND libs Qt5::Core Qt5::Widgets Qt5::OpenGL Qt5::Network)
set(SRC_QT Core Widgets OpenGL Network)
foreach(component ${SRC_QT})
    list(APPEND incs ${Qt5${component}_INCLUDE_DIRS})
    list(APPEND libs Qt5::${component})
endforeach()
if (WIN32)
    list(APPEND libs Qt5::WinMain)
endif()

# ODE
list(APPEND incs ${ODE_INCLUDE_DIRS})
list(APPEND libs ${ODE_LIBRARIES})
if(APPLE)
add_definitions(-DdIDEDOUBLE)
else()
add_definitions(-DdDOUBLE)
endif()

# Protobuf
list(APPEND incs ${Protobuf_INCLUDE_DIR})
list(APPEND libs ${Protobuf_LIBRARY_RELEASE} ${Protobuf_LITE_LIBRARY_RELEASE} ${Protobuf_PROTOC_LIBRARY_RELEASE})

## vartypes
list(APPEND incs ${VARTYPES_INCLUDE_DIRS})
list(APPEND libs ${VARTYPES_LIBRARIES})

# project files
## protobuf files
set(PROTO_LIST
    messages_robocup_ssl_detection
    messages_robocup_ssl_geometry
    messages_robocup_ssl_wrapper
    messages_robocup_ssl_refbox_log
    messages_robocup_ssl_robot_status
    grSim_Replacement
    grSim_Commands
    grSim_Packet
)
get_pb_file(PROTO_H PROTO_CPP ${PROTO_LIST})

set(PROJECT_INCLUDE_DIRS
    ${CMAKE_BINARY_DIR}/proto
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/net
    ${CMAKE_CURRENT_SOURCE_DIR}/include/physics
    ${CMAKE_SOURCE_DIR}/share
)
include_directories(${PROJECT_INCLUDE_DIRS} ${incs})

## cpp files
aux_source_directory(./src CPPFILES)
aux_source_directory(./src/physics PHYSICS_CPPFILES)
aux_source_directory(./src/net NET_CPPFILES)
aux_source_directory(${CMAKE_SOURCE_DIR}/share SHARE_CPPFILES)

## header files
FILE(GLOB HEADERFILES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
FILE(GLOB PHYSICS_HEADERFILES "${CMAKE_CURRENT_SOURCE_DIR}/include/physics/*.h")
FILE(GLOB NET_HEADERFILES "${CMAKE_CURRENT_SOURCE_DIR}/include/net/*.h")
FILE(GLOB SHARE_HEADERFILES "${CMAKE_SOURCE_DIR}/share/*.h")

## resource files
FILE(GLOB RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/resources/*.qrc" "${CMAKE_CURRENT_SOURCE_DIR}/resources/*.rc")

# for VS solution file
IF(WIN32)
source_group("include" FILES ${HEADERFILES})
source_group("include\\physics" FILES ${PHYSICS_HEADERFILES})
source_group("include\\net" FILES ${NET_HEADERFILES})
source_group("include\\share" FILES ${SHARE_HEADERFILES})

source_group("src" FILES ${CPPFILES})
source_group("src\\physics" FILES ${PHYSICS_CPPFILES})
source_group("src\\net" FILES ${NET_CPPFILES})
source_group("src\\share" FILES ${SHARE_CPPFILES})

source_group("resources" FILES ${RESOURCES})
ENDIF()

# files to be compiled
set(srcs
    ${PROTO_CPP}
    ${PROTO_H}
    ${RESOURCES}

    ${HEADERFILES}
    ${PHYSICS_HEADERFILES}
    ${NET_HEADERFILES}
    ${SHARE_HEADERFILES}

    ${CPPFILES}
    ${PHYSICS_CPPFILES}
    ${NET_CPPFILES}
    ${SHARE_CPPFILES}
)

add_executable(${TARGET_NAME} ${srcs})
target_link_libraries(${TARGET_NAME} PRIVATE ${libs})
