cmake_minimum_required(VERSION 3.12)
project(Falcon LANGUAGES CXX)

set(VERSION "0.0.1")
set(VENDOR "SRC")
set(MAINTAINER "SRC <sjtu_src2020@163.com>")

include(${PROJECT_SOURCE_DIR}/cmake/Utils.cmake)
standard_config()
standard_paths(${PROJECT_SOURCE_DIR} bin/base lib pdb)

include(${PROJECT_SOURCE_DIR}/cmake/GetThirdParty.cmake)

function(get_pb_file H CPP)
	list(APPEND PH ${ARGN})
	list(APPEND PC ${ARGN})
	list(TRANSFORM PH PREPEND ${CMAKE_BINARY_DIR}/proto/)
	list(TRANSFORM PH APPEND .pb.h)
	list(TRANSFORM PC PREPEND ${CMAKE_BINARY_DIR}/proto/)
	list(TRANSFORM PC APPEND .pb.cc)
	set(${H} ${PH} PARENT_SCOPE)
	set(${CPP} ${PC} PARENT_SCOPE)
endfunction()
set(PROTO_META_BASE_DIR ${CMAKE_BINARY_DIR}/proto)
set(PROTO_FILE_DIR ${CMAKE_SOURCE_DIR}/share/proto)
file(MAKE_DIRECTORY ${PROTO_META_BASE_DIR})
list(APPEND PROTO_FLAGS -I${PROTO_FILE_DIR})
file(GLOB PROTO_FILES "${PROTO_FILE_DIR}/*.proto")

FOREACH(FIL ${PROTO_FILES})
	GET_FILENAME_COMPONENT(ABS_FIL ${FIL} ABSOLUTE)
	GET_FILENAME_COMPONENT(FIL_WE ${ABS_FIL} NAME_WE)
	EXECUTE_PROCESS(
		COMMAND ${Protobuf_PROTOC_EXECUTABLE} ${PROTO_FLAGS} --cpp_out=${PROTO_META_BASE_DIR} ${FIL}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
ENDFOREACH()

add_subdirectory(Client)
add_subdirectory(Core)
# add_subdirectory(Controller)

include(${PROJECT_SOURCE_DIR}/cmake/CopyThirdParty.cmake)
