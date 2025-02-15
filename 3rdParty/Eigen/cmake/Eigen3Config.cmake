# This file exports the Eigen3::Eigen CMake target which should be passed to the
# target_link_libraries command.

@PACKAGE_INIT@

include ("${CMAKE_CURRENT_LIST_DIR}/Eigen3Targets.cmake")

# Legacy variables, do *not* use. May be removed in the future.

set (EIGEN3_FOUND 1)
set (EIGEN3_USE_FILE    "${CMAKE_CURRENT_LIST_DIR}/UseEigen3.cmake")

set (EIGEN3_DEFINITIONS  "")
set (EIGEN3_INCLUDE_DIR  "${PACKAGE_PREFIX_DIR}/include/eigen3")
set (EIGEN3_INCLUDE_DIRS "{PACKAGE_PREFIX_DIR}/include/eigen3")
set (EIGEN3_ROOT_DIR     "${PACKAGE_PREFIX_DIR}")

set (EIGEN3_VERSION_STRING "3.4.0")
set (EIGEN3_VERSION_MAJOR  "3")
set (EIGEN3_VERSION_MINOR  "4")
set (EIGEN3_VERSION_PATCH  "0")
