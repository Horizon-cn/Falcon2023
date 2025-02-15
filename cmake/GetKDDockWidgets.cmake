# define
option(KDDOCKWIDGETS_QTQUICK ON)
option(KDDOCKWIDGETS_QT6 OFF)
add_definitions(-DKDDOCKWIDGETS_QTQUICK)
add_definitions(-DKDDOCKWIDGETS_QT6)

IF (WIN32)
	# include(${THIRDPARTY_LIB_DIR}/kddockwidgets/cmake/KDDockWidgetsConfig.cmake)

	set(KDDockWidgets_DIR ${THIRDPARTY_LIB_DIR}/kddockwidgets-1.5.0)

	list(APPEND CMAKE_PREFIX_PATH ${KDDockWidgets_DIR})
	message("Find KDDockWidgets : ${KDDockWidgets_DIR}")
	set(KDDOCKWIDGETS_INCLUDE_DIRS "${KDDockWidgets_DIR}/include")
	set(KDDOCKWIDGETS_LIBRARIES_DEBUG "${KDDockWidgets_DIR}/lib/kddockwidgetsd.lib")
	set(KDDOCKWIDGETS_LIBRARIES_RELEASE "${KDDockWidgets_DIR}/lib/kddockwidgets.lib")
	list(APPEND CMAKE_PREFIX_PATH ${KDDOCKWIDGETS_INCLUDE_DIRS} ${KDDOCKWIDGETS_LIBRARIES_DEBUG} ${KDDOCKWIDGETS_LIBRARIES_RELEASE})
	message("${KDDOCKWIDGETS_INCLUDE_DIRS} ${KDDOCKWIDGETS_LIBRARIES_DEBUG} ${KDDOCKWIDGETS_LIBRARIES_RELEASE}")
ELSE()
	find_package(KDDockWidgets REQUIRED)
ENDIF()
