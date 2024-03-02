cmake_minimum_required(VERSION 3.8)

project(gpsTrackSysEmulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -Wall -fprofile-arcs -ftest-coverage -lgcov")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

include_directories(
    ${PROJECT_SOURCE_DIR}/
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/test
)

add_library(libraries STATIC
    src/HTTPRequest.hpp
    src/Utils.hpp src/Utils.cpp
    src/Device.hpp src/Device.cpp
)

target_link_libraries(libraries
    rpcrt4.lib
    ws2_32.lib
)

add_executable(emulator src/Emulator.cpp)
target_compile_options(emulator PUBLIC "--coverage")
target_link_libraries(emulator
    libraries
    gcov
)

add_executable(testDevice test/testDevice.cpp)
#target_compile_options(testDevice PUBLIC "-O0" "-fprofile-arcs" "-ftest-coverage")
target_link_libraries(testDevice
    libraries
)

include(CTest)
enable_testing()

# TESTING

add_test(NAME testDeviceConstruct COMMAND testDevice
    "testDeviceConstruct"
)
add_test(NAME testDeviceCopyConstruct COMMAND testDevice
    "testDeviceCopyConstruct"
)
add_test(NAME testDeviceMoveNorth COMMAND testDevice
    "testDeviceMoveNorth"
)
add_test(NAME testDeviceMoveNortheast COMMAND testDevice
    "testDeviceMoveNortheast"
)
add_test(NAME testDeviceMoveEast COMMAND testDevice
    "testDeviceMoveEast"
)
add_test(NAME testDeviceMoveSoutheast COMMAND testDevice
    "testDeviceMoveSoutheast"
)
add_test(NAME testDeviceMoveSouth COMMAND testDevice
    "testDeviceMoveSouth"
)
add_test(NAME testDeviceMoveSouthwest COMMAND testDevice
    "testDeviceMoveSouthwest"
)
add_test(NAME testDeviceMoveWest COMMAND testDevice
    "testDeviceMoveWest"
)
add_test(NAME testDeviceMoveNorthwest COMMAND testDevice
    "testDeviceMoveNorthwest"
)
add_test(NAME testDeviceMoveErrdir COMMAND testDevice
    "testDeviceMoveErrdir"
)
add_test(NAME testDeviceMoveErrlat COMMAND testDevice
    "testDeviceMoveErrlat"
)
add_test(NAME testDeviceMoveErrlot COMMAND testDevice
    "testDeviceMoveErrlot"
)
add_test(NAME testDeviceSendError COMMAND testDevice
    "testDeviceSendError"
)