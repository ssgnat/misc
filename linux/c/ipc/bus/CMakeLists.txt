cmake_minimum_required(VERSION 2.6)

function(dbg)
    set(tmp "")
    foreach(arg IN LISTS ARGN)
        set(tmp "${tmp} ${arg}")
    endforeach()
    message(STATUS "${CMAKE_PROJECT_NAME}:   ${tmp}")
endfunction()

SET(CMAKE_SYSTEM_NAME Linux) #comment indicates android
SET(CMAKE_BUILD_TYPE Debug)
ADD_DEFINITIONS(-Os -Wall -Werror --std=gnu99 -g3 -Wmissing-declarations)

SET(UBUS_UNIX_SOCKET "/tmp/hzbus.sock")
SET(UBUS_MAX_MSGLEN 1048576)
ADD_DEFINITIONS(-DUBUS_UNIX_SOCKET="${UBUS_UNIX_SOCKET}")
ADD_DEFINITIONS(-DUBUS_MAX_MSGLEN=${UBUS_MAX_MSGLEN})

OPTION(BUILD_LUA "build Lua plugin" OFF)
OPTION(BUILD_CONDUIT "build conduit" ON)
OPTION(ENABLE_SYSTEMD "systemd support" OFF)

ADD_DEFINITIONS(-DDEBUG)

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
    ADD_DEFINITIONS(-DLINUX)
    SET(CMAKE_C_COMPILER   "arm-himix200-linux-gcc")
    SET(CMAKE_CXX_COMPILER "arm-himix200-linux-g++")
ELSE(CMAKE_SYSTEM_NAME MATCHES "android")
    ADD_DEFINITIONS(-DANDROID)
    SET(CMAKE_C_COMPILER   "arm-linux-androideabi-gcc")
    SET(CMAKE_CXX_COMPILER   "arm-linux-androideabi-g++")
ENDIF()

PROJECT(hzbus)
SET(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")

EXECUTE_PROCESS(COMMAND rm -rf bin_bak lib_bak include WORKING_DIRECTORY ../)
EXECUTE_PROCESS(COMMAND mv bin bin_bak WORKING_DIRECTORY ../)
EXECUTE_PROCESS(COMMAND mv lib lib_bak WORKING_DIRECTORY ../)
EXECUTE_PROCESS(COMMAND mkdir bin lib include WORKING_DIRECTORY ../)

IF(APPLE)
    INCLUDE_DIRECTORIES(/opt/local/include)
    LINK_DIRECTORIES(/opt/local/lib)
ENDIF()

dbg(${CMAKE_CURRENT_LIST_LINE} ${CMAKE_SYSTEM_NAME} ${CMAKE_BUILD_TYPE})
#ADD_SUBDIRECTORY(json)
#ADD_SUBDIRECTORY(lua)
ADD_SUBDIRECTORY(libubox)

INCLUDE_DIRECTORIES(.)
ADD_LIBRARY(hzbus SHARED libubus.c libubus-io.c libubus-obj.c libubus-sub.c libubus-req.c)
TARGET_LINK_LIBRARIES(hzbus ubox m)

ADD_EXECUTABLE(hzbusd ubusd.c ubusd_id.c ubusd_obj.c ubusd_proto.c ubusd_event.c)
TARGET_LINK_LIBRARIES(hzbusd ubox)

find_library(json libjson-c.a ${PROJECT_SOURCE_DIR}/json)
ADD_EXECUTABLE(cli cli.c)
#SET_TARGET_PROPERTIES(cli PROPERTIES OUTPUT_NAME hzbus)
#TARGET_LINK_LIBRARIES(cli hzbus ubox blobmsg_json_s ${json})
TARGET_LINK_LIBRARIES(cli hzbus ubox blobmsg_json_s m)

IF(BUILD_CONDUIT)
    ADD_SUBDIRECTORY(ubus_conduit)
ENDIF()

#INSTALL(TARGETS hzbus cli hzbusd DESTINATION bin)
INSTALL(FILES ubusmsg.h ubus_common.h libubus.h DESTINATION ${PROJECT_SOURCE_DIR}/include)

# FIXME: this works but certainly can be done better:
SET(UBUSD_BINARY "${CMAKE_INSTALL_PREFIX}/sbin/ubusd")

# do this after the installs so we have the proper paths
IF(ENABLE_SYSTEMD)
    INCLUDE(FindPkgConfig)
    PKG_CHECK_MODULES(SYSTEMD systemd)
    IF(SYSTEMD_FOUND)
        ADD_SUBDIRECTORY(systemd)
    ENDIF()
ENDIF()

INSTALL(TARGETS hzbusd DESTINATION ${PROJECT_SOURCE_DIR}/bin/)
INSTALL(TARGETS hzbus DESTINATION ${PROJECT_SOURCE_DIR}/lib/)
INSTALL(FILES ./build/cli DESTINATION ${PROJECT_SOURCE_DIR}/bin/
    PERMISSIONS  OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE
    RENAME hzbus)
#INSTALL(TARGETS libhzbus.so  DESTINATION ../bin/lib/)
