
# copy ode dll to ZBin
IF(WIN32)
file(COPY ${THIRDPARTY_LIB_DIR}/ODE/bin/ode_double.dll DESTINATION ${CMAKE_SOURCE_DIR}/ZBin/)
ENDIF()

# copy lua dll to ZBin
IF(WIN32)
file(COPY ${THIRDPARTY_LIB_DIR}/lua/bin/lua5.1.dll DESTINATION ${CMAKE_SOURCE_DIR}/ZBin/)
ENDIF()
