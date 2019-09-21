cmake_minimum_required(VERSION 2.6)
INCLUDE(CheckLibraryExists)
INCLUDE(CheckFunctionExists)

PROJECT(ubox C)
ADD_DEFINITIONS(-Os -Wall -Werror --std=gnu99 -g3 -Wmissing-declarations)

OPTION(BUILD_LUA "build Lua plugin" OFF)

IF(APPLE)
  INCLUDE_DIRECTORIES(/opt/local/include)
  LINK_DIRECTORIES(/opt/local/lib)
ENDIF()

INCLUDE(FindPkgConfig)
#PKG_CHECK_MODULES(JSONC libjson-c.so /home/tangss/work/code/hzsvn/saturn/3rd/ubus/bin/lib)

SET(JSONC_FOUND TRUE)
SET(JSONC_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/../json/)
IF(JSONC_FOUND)
  MESSAGE("JSON --- 2")
  ADD_DEFINITIONS(-DJSONC)
  INCLUDE_DIRECTORIES(${JSONC_INCLUDE_DIRS})
ENDIF()

SET(SOURCES avl.c avl-cmp.c blob.c blobmsg.c uloop.c usock.c ustream.c ustream-fd.c vlist.c utils.c safe_list.c runqueue.c md5.c)

ADD_LIBRARY(ubox SHARED ${SOURCES})

SET(LIBS)
CHECK_FUNCTION_EXISTS(clock_gettime HAVE_GETTIME)
IF(NOT HAVE_GETTIME)
	CHECK_LIBRARY_EXISTS(rt clock_gettime "" NEED_GETTIME)
	IF(NEED_GETTIME)
		TARGET_LINK_LIBRARIES(ubox rt)
	ENDIF()
ENDIF()

FILE(GLOB headers *.h)
INSTALL(FILES ${headers}
	DESTINATION include/libubox
)
INSTALL(TARGETS ubox
	LIBRARY DESTINATION lib
)

ADD_SUBDIRECTORY(lua)

find_library(json libjson-c.so ${PROJECT_SOURCE_DIR}/../bin/lib/)
IF(EXISTS ${json})
    MESSAGE("JSON ---")
    ADD_LIBRARY(blobmsg_json SHARED blobmsg_json.c)
	TARGET_LINK_LIBRARIES(blobmsg_json ubox ${json} m)

    ADD_LIBRARY(blobmsg_json_s STATIC blobmsg_json.c)
	TARGET_LINK_LIBRARIES(blobmsg_json_s ubox ${json} m)

	ADD_EXECUTABLE(jshn jshn.c)
	TARGET_LINK_LIBRARIES(jshn ${json})

    ADD_LIBRARY(json_script SHARED json_script.c)
	TARGET_LINK_LIBRARIES(json_script ubox)

	INSTALL(TARGETS blobmsg_json jshn json_script
		LIBRARY DESTINATION lib
		RUNTIME DESTINATION bin
	)

	FILE(GLOB scripts sh/*.sh)
	INSTALL(FILES ${scripts}
		DESTINATION share/libubox
	)

ENDIF()

add_custom_command(
     TARGET blobmsg_json
     POST_BUILD
     COMMAND cp ./*.so ../../bin/lib/ | echo 0
     COMMAND cp ./*.a  ../../bin/lib/ | echo 0
     )
