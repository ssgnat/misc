# Install script for directory: /home/tangshishan/tmp/misc/linux/c/ipc/bus/ubus_conduit

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
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_cli.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_cli.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_cli.so"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_cli.so")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib" TYPE SHARED_LIBRARY FILES "/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/ubus_conduit/libconduit_cli.so")
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_cli.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_cli.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_cli.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-strip" "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_cli.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_srv.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_srv.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_srv.so"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_srv.so")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib" TYPE SHARED_LIBRARY FILES "/home/tangshishan/tmp/misc/linux/c/ipc/bus/build/ubus_conduit/libconduit_srv.so")
  IF(EXISTS "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_srv.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_srv.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_srv.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/home/tangshishan/arm-himix200-linux/bin/arm-himix200-linux-strip" "$ENV{DESTDIR}/home/tangshishan/tmp/misc/linux/c/ipc/bus/lib/libconduit_srv.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/conduit_client.h;/home/tangshishan/tmp/misc/linux/c/ipc/bus/include/conduit_server.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/home/tangshishan/tmp/misc/linux/c/ipc/bus/include" TYPE FILE FILES
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/ubus_conduit/conduit_client.h"
    "/home/tangshishan/tmp/misc/linux/c/ipc/bus/ubus_conduit/conduit_server.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

