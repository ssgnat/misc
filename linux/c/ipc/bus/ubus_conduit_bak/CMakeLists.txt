cmake_minimum_required(VERSION 2.6)


set(CMAKE_C_COMPILER "arm-linux-androideabi-gcc")

MESSAGE("CC:" $ENV{CC})

ADD_DEFINITIONS(-I..)
ADD_DEFINITIONS(-I.)
INCLUDE_DIRECTORIES(../ ${CMAKE_CURRENT_SOURCE_DIR}/..)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/../../../../conduit/)

ADD_LIBRARY(conduit_srv SHARED conduit_server.c )
TARGET_LINK_LIBRARIES(conduit_srv hzbus ubox blobmsg_json log)

ADD_LIBRARY(conduit_cli SHARED conduit_client.c )
TARGET_LINK_LIBRARIES(conduit_cli hzbus ubox blobmsg_json log)

#add_custom_command(
#     TARGET conduit_cli
#     POST_BUILD
#     COMMAND cp ${PROJECT_SOURCE_DIR}/conduit_client.h ${PROJECT_SOURCE_DIR}/../bin/lib/include/client/
#     COMMAND cp ${PROJECT_SOURCE_DIR}/conduit_server.h ${PROJECT_SOURCE_DIR}/../bin/lib/include/server/
#     COMMAND cp ${PROJECT_SOURCE_DIR}/conduit_common.h ${PROJECT_SOURCE_DIR}/../bin/lib/include/client/
#     COMMAND cp ${PROJECT_SOURCE_DIR}/conduit_common.h ${PROJECT_SOURCE_DIR}/../bin/lib/include/server/
#     COMMAND cp ${PROJECT_SOURCE_DIR}/build/*.so ${PROJECT_SOURCE_DIR}/../bin/lib/
#     )

#IF (DEBUG)
#	ADD_DEFINITIONS(-DDEBUG=1)
#	ADD_EXECUTABLE(test_server_debug test_server_main.c)
#	TARGET_LINK_LIBRARIES(test_server_debug conduit_srv hzbus ubox blobmsg_json)
#	ADD_EXECUTABLE(test_client_debug test_client_main.c conduit_client.c )
#	TARGET_LINK_LIBRARIES(test_client_debug conduit_client hzbus ubox blobmsg_json)
#ENDIF()


