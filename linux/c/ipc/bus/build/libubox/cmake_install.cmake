# Install script for directory: /home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox

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
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/list.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/safe_list.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/utils.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/runqueue.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/blob.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/md5.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/usock.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/ustream.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/json_script.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/blobmsg_json.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/blobmsg.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/uloop.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/avl.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/avl-cmp.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox/vlist.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/include/libubox" TYPE FILE FILES
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/list.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/safe_list.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/utils.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/runqueue.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/blob.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/md5.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/usock.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/ustream.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/json_script.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/blobmsg_json.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/blobmsg.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/uloop.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/avl.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/avl-cmp.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/vlist.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox/libubox.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libubox.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libblobmsg_json.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libblobmsg_json.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libblobmsg_json.so"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libblobmsg_json.so")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib" TYPE SHARED_LIBRARY FILES "/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox/libblobmsg_json.so")
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libblobmsg_json.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libblobmsg_json.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libblobmsg_json.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-strip" "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libblobmsg_json.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson_script.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson_script.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson_script.so"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson_script.so")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib" TYPE SHARED_LIBRARY FILES "/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox/libjson_script.so")
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson_script.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson_script.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson_script.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-strip" "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libjson_script.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libubox.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libubox.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libubox.so"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libubox.so")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib" TYPE SHARED_LIBRARY FILES "/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox/libubox.so")
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libubox.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libubox.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-strip" "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libubox.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/bin/jshn" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/bin/jshn")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/bin/jshn"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/tangshishan/tmp/misc/linux/c/ipc/bus/bin/jshn")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/home/tangshishan/tmp/misc/linux/c/ipc/bus/bin" TYPE EXECUTABLE FILES "/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox/jshn")
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/bin/jshn" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/bin/jshn")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/bin/jshn")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-strip" "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/bin/jshn")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/libubox" TYPE FILE FILES "/home/tangshishan/tmp/misc/linux/c/ipc/bus/libubox/sh/jshn.sh")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox/json/cmake_install.cmake")
  INCLUDE("/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/libubox/lua/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

