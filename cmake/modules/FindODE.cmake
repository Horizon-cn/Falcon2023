IF (WIN32)
    set(ODE_INCLUDE_DIRS "${THIRDPARTY_LIB_DIR}/ODE/include")
    set(ODE_LIBRARIES "${THIRDPARTY_LIB_DIR}/ODE/lib/ode.lib")
    list(APPEND CMAKE_PREFIX_PATH ${ODE_INCLUDE_DIRS} ${ODE_LIBRARIES})
    message("Find ODE : ${ODE_INCLUDE_DIRS} ${ODE_LIBRARIES}")
ELSE ()
    find_path(
       ODE_INCLUDE_DIRS
       NAMES
       ode/ode.h
       HINTS
       $ENV{HOME}/include
       /usr/local/include
       /usr/include
       $ENV{ProgramFiles}/ode/include
       ${THIRDPARTY_LIB_DIR}/ODE/include
    )

    find_library(
       ODE_LIBRARIES
       NAMES
       ode
       HINTS
       ${THIRDPARTY_LIB_DIR}/ODE/lib
    )

    find_library(
       ODE_LIBRARY_DEBUG
       NAMES
       oded debugdll/ode
       HINTS
       $ENV{HOME}/lib
       /usr/local/lib
       /usr/lib
       $ENV{ProgramFiles}/ode/lib
    )

    find_library(
       ODE_LIBRARY_RELEASE
       NAMES
       ode releasedll/ode
       HINTS
       $ENV{HOME}/lib
       /usr/local/lib
       /usr/lib
       $ENV{ProgramFiles}/ode/lib
    )

    if(ODE_LIBRARY_DEBUG AND NOT ODE_LIBRARY_RELEASE)
       set(ODE_LIBRARIES ${ODE_LIBRARY_DEBUG})
    endif()

    if(ODE_LIBRARY_RELEASE AND NOT ODE_LIBRARY_DEBUG)
       set(ODE_LIBRARIES ${ODE_LIBRARY_RELEASE})
    endif()

    if(ODE_LIBRARY_DEBUG AND ODE_LIBRARY_RELEASE)
       set(ODE_LIBRARIES debug ${ODE_LIBRARY_DEBUG} optimized ${ODE_LIBRARY_RELEASE})
    endif()

    find_package_handle_standard_args(
       ODE
       DEFAULT_MSG
       ODE_INCLUDE_DIRS
       ODE_LIBRARIES
    )

    mark_as_advanced(
        ODE_INCLUDE_DIRS
        ODE_LIBRARIES
        ODE_LIBRARY_DEBUG
        ODE_LIBRARY_RELEASE
    )
ENDIF ()
