
# copy ode dll
IF(WIN32)
file(COPY ${THIRDPARTY_LIB_DIR}/ODE/bin/ode_double.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
ENDIF()

# copy lua dll
IF(WIN32)
file(COPY ${THIRDPARTY_LIB_DIR}/lua/bin/lua5.1.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
ENDIF()

# copy boost dll
# IF(WIN32)
# 	foreach(component ${BOOST_COMPONENTS})
#         copy_if_not_exists(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/boost_${component}.dll ${BOOST_DIR}/lib/boost_${component}.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#     endforeach()
#     unset(vc_version)
# ENDIF()

# copy kddockwidgets dll
# IF(WIN32)
# 	IF(CMAKE_CONFIGURATION_TYPES STREQUAL "Debug")
# 		file(COPY ${KDDockWidgets_DIR}/bin/kddockwidgetsd.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
# 	ELSE()
# 		file(COPY ${KDDockWidgets_DIR}/bin/kddockwidgets.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
# 	ENDIF()
# ENDIF()
