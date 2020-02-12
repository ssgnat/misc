
cmake_minimum_required(VERSION 2.8)

include_directories(.)
include_directories(../)
add_library(conduit_client_native_lib SHARED conduit_client_native_lib.c)
link_directories(${CMAKE_SOURCE_DIR})
#link_directories(${CMAKE_SOURCE_DIR}/conduit/lib/)
MESSAGE(${CMAKE_SOURCE_DIR})
MESSAGE(${CMAKE_C_COMPILER})

target_link_libraries(conduit_client_native_lib ${CMAKE_SOURCE_DIR}/../libconduit_cli.so log)

