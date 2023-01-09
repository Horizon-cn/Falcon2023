# boost >= 1.77.0

# set boost path
IF(WIN32 AND CMAKE_CL_64)
    set(BOOST_DIR "${THIRDPARTY_LIB_DIR}/boost_1_77_0_x64")
ENDIF()

add_definitions(-DBOOST_ALL_DYN_LINK)

set(BOOST_ROOT ${BOOST_DIR})
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_DEBUG ON)

IF(WIN32)
    set(Boost_LIB_VERSION "1_77")

    IF(Boost_LIB_VERSION STREQUAL "1_77")
        set(vc_version "vc142")
    ELSEIF(MSVC14)
        set(vc_version "vc140")
    ELSEIF(MSVC10)
        set(vc_version "vc100")
    ENDIF()

    set(version "32")
    IF(CMAKE_CL_64)
      set(version "64")
    ENDIF()

    set(BOOST_COMPONENTS)
    set(BOOST_COMPONENT_NAMES filesystem thread chrono)
    foreach(component ${BOOST_COMPONENT_NAMES})
        list(APPEND BOOST_COMPONENTS ${component}-${vc_version}-mt-x${version}-${Boost_LIB_VERSION})
    endforeach()
    find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
ELSE()
    find_package(Boost 1.77.0 REQUIRED)
ENDIF()    
