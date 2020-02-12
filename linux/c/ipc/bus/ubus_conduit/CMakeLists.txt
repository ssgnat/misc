cmake_minimum_required(VERSION 2.6)


project(conduit)

ADD_DEFINITIONS(-I..)
ADD_DEFINITIONS(-I.)
INCLUDE_DIRECTORIES(../ ${CMAKE_CURRENT_SOURCE_DIR}/..)

ADD_LIBRARY(conduit_srv SHARED conduit_server.c )

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/build)

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    TARGET_LINK_LIBRARIES(conduit_srv hzbus ubox blobmsg_json)
ELSE(CMAKE_SYSTEM_NAME MATCHES "android")
    TARGET_LINK_LIBRARIES(conduit_srv hzbus ubox blobmsg_json log)
ENDIF()

ADD_LIBRARY(conduit_cli SHARED conduit_client.c)
IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    TARGET_LINK_LIBRARIES(conduit_cli hzbus ubox blobmsg_json)
ELSE(CMAKE_SYSTEM_NAME MATCHES "android")
    TARGET_LINK_LIBRARIES(conduit_cli hzbus ubox blobmsg_json log)
ENDIF()

INSTALL(TARGETS conduit_cli conduit_srv DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/)
INSTALL(FILES conduit_client.h conduit_server.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/)
