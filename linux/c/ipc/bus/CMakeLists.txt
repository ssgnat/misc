cmake_minimum_required(VERSION 2.6)

PROJECT(hzbus C)
ADD_DEFINITIONS(-Os -Wall -Werror --std=gnu99 -g3 -Wmissing-declarations)

OPTION(BUILD_LUA "build Lua plugin" OFF)
OPTION(BUILD_CONDUIT "build conduit" ON)
OPTION(ENABLE_SYSTEMD "systemd support" OFF)

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
SET(UBUS_UNIX_SOCKET "/var/run/ubus.sock")
SET(UBUS_MAX_MSGLEN 1048576)

ADD_DEFINITIONS( -DUBUS_UNIX_SOCKET="${UBUS_UNIX_SOCKET}")
ADD_DEFINITIONS( -DUBUS_MAX_MSGLEN=${UBUS_MAX_MSGLEN})

IF(APPLE)
  INCLUDE_DIRECTORIES(/opt/local/include)
  LINK_DIRECTORIES(/opt/local/lib)
ENDIF()

INCLUDE_DIRECTORIES(.)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/bin/lib)
MESSAGE(WARNING "TEST DIR:"${PROJECT_SOURCE_DIR}/bin/lib)
ADD_LIBRARY(hzbus SHARED libubus.c libubus-io.c libubus-obj.c libubus-sub.c libubus-req.c)
TARGET_LINK_LIBRARIES(hzbus ubox m)

ADD_EXECUTABLE(hzbusd ubusd.c ubusd_id.c ubusd_obj.c ubusd_proto.c ubusd_event.c)
TARGET_LINK_LIBRARIES(hzbusd ubox)

find_library(json libjson-c.a ${PROJECT_SOURCE_DIR}/json)
ADD_EXECUTABLE(cli cli.c)
SET_TARGET_PROPERTIES(cli PROPERTIES OUTPUT_NAME hzbus)
#TARGET_LINK_LIBRARIES(cli hzbus ubox blobmsg_json_s ${json})
TARGET_LINK_LIBRARIES(cli hzbus ubox blobmsg_json_s m)


ADD_SUBDIRECTORY(lua)
ADD_SUBDIRECTORY(libubox)
#ADD_SUBDIRECTORY(ubus_conduit)

INSTALL(TARGETS hzbus cli
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)
INSTALL(TARGETS hzbusd
	RUNTIME DESTINATION bin
)

INSTALL(FILES ubusmsg.h ubus_common.h libubus.h DESTINATION include)

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

add_custom_command(
    TARGET cli
    POST_BUILD
    COMMAND cp ./hzbus ../bin/
    )

add_custom_command(
    TARGET hzbus
    POST_BUILD
    COMMAND cp ./*.so ../bin/lib/
    )

add_custom_command(
    TARGET hzbusd
    POST_BUILD
    COMMAND cp ./hzbusd ../bin/
    )
