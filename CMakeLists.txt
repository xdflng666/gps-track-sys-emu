cmake_minimum_required(VERSION 3.8)

project(gpsTrackSysEmulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-O0 -g --coverage")
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
    uuid
)

add_executable(emulator src/Emulator.cpp)
target_link_libraries(emulator
    libraries
)

add_executable(testDevice test/testDevice.cpp)
target_link_libraries(testDevice
    libraries
)

add_executable(testUtils test/testUtils.cpp)
target_link_libraries(testUtils
    libraries
)

include(CTest)
enable_testing()


# =================
#    Test Device
# =================

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
add_test(NAME testDeviceSend COMMAND testDevice
    "testDeviceSend"
)
add_test(NAME testDeviceSendError COMMAND testDevice
    "testDeviceSendError"
)
add_test(NAME testDeviceInitDevices COMMAND testDevice
    "testDeviceInitDevices"
)
add_test(NAME testDeviceSeveralInit COMMAND testDevice
    "testDeviceSeveralInit"
)

# =================
#    Test Utils
# =================

add_test(NAME testUtilsCheckEnterParamsInvalidPeram COMMAND testUtils
    "testUtilsCheckEnterParamsInvalidPeram"
)
add_test(NAME testUtilsCheckEnterParamsNegativeValue COMMAND testUtils
    "testUtilsCheckEnterParamsNegativeValue"
)
add_test(NAME testUtilsCheckEnterParamsInvalidUrl COMMAND testUtils
    "testUtilsCheckEnterParamsInvalidUrl"
)
add_test(NAME testUtilsCheckEnterParamsSuccess COMMAND testUtils
    "testUtilsCheckEnterParamsSuccess"
)
add_test(NAME testUtilsCheckEnterParamsSuccessValue COMMAND testUtils
    "testUtilsCheckEnterParamsSuccessValue"
)
add_test(NAME testUtilsRandomCoordInSpb COMMAND testUtils
    "testUtilsRandomCoordInSpb"
)