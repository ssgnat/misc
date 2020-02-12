# Install script for directory: /home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/tangshishan/tmp/misc/linux/c/ipc/bus")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox/json/libjson-c.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson-c.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson-c.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson-c.so"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson-c.so")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib" TYPE SHARED_LIBRARY FILES "/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox/json/libjson-c.so")
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson-c.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson-c.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-strip" "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson-c.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/pkgconfig/json-c.pc")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/pkgconfig" TYPE FILE FILES "/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox/json/json-c.pc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/config.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/json_config.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/json.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/arraylist.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/debug.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/json_c_version.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/json_inttypes.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/json_object.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/json_object_iterator.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/json_pointer.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/json_tokener.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/json_util.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/linkhash.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c/printbuf.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/json-c" TYPE FILE FILES
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox/json/config.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox/json/json_config.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json/json.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json/arraylist.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json/debug.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json/json_c_version.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json/json_inttypes.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json/json_object.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json/json_object_iterator.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json/json_pointer.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json/json_tokener.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json/json_util.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json/linkhash.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json/printbuf.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

