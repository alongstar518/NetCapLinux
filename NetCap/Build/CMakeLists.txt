cmake_minimum_required(VERSION 2.6)

set(PROJECT_PATH /home/kenn/Projects)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_PATH}/NetCap/Build/Out)

include_directories(BEFORE ${PROJECT_PATH}/NetCap/Include)

file(GLOB INPUT_SRCS ${PROJECT_PATH}/NetCap/src/*.c)

LINK_LIBRARIES(${PROJECT_PATH}/NetCap/lib/libpcap.so.1.7.4 /home/kenn/BRCMToolChain/stbgcc-4.8-1.2/arm-linux-gnueabihf/sys-root/usr/lib/libpthread.so)

add_executable(netcap ${INPUT_SRCS})



