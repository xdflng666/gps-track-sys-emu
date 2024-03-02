#include <iostream>
#include <cassert>

#include "Device.hpp"
#include "Utils.hpp"

std::map<std::string, int> tests = { { "testDeviceConstruct",      1 },
                                     { "testDeviceCopyConstruct",  2 },
                                     { "testDeviceMoveNorth",      3 },
                                     { "testDeviceMoveNortheast",  4 },
                                     { "testDeviceMoveEast",       5 },
                                     { "testDeviceMoveSoutheast",  6 },
                                     { "testDeviceMoveSouth",      7 },
                                     { "testDeviceMoveSouthwest",  8 },
                                     { "testDeviceMoveWest",       9 },
                                     { "testDeviceMoveNorthwest", 10 },
                                     { "testDeviceMoveErrdir",    11 },
                                     { "testDeviceMoveErrlat",    12 },
                                     { "testDeviceMoveErrlot",    13 },
                                     { "testDeviceSend",          14 },
                                     { "testDeviceSendError",     15 } };

void testDeviceConstruct();
void testDeviceCopyConstruct();
void testDeviceMove(int choice);
void testDeviceSend();
void testDeviceSendError();

int main(int argc, char* argv[])
{
    int choice = 0;

    if (argc != 2)
    {
        printColoredText("Invalid argument", FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << ": specify the name of test";
		return RetCodes::ERR_INVALID_PARAM;
    }

    choice = tests.find(argv[1])->second;

    switch (choice)
    {
        case 1:
        {
            testDeviceConstruct();
            break;
        }
        case 2:
        {
            testDeviceCopyConstruct();
            break;
        }
        case 3:
        {
            testDeviceMove(0);
            break;
        }
        case 4:
        {
            testDeviceMove(1);
            break;
        }
        case 5:
        {
            testDeviceMove(2);
            break;
        }
        case 6:
        {
            testDeviceMove(3);
            break;
        }
        case 7:
        {
            testDeviceMove(4);
            break;
        }
        case 8:
        {
            testDeviceMove(5);
            break;
        }
        case 9:
        {
            testDeviceMove(6);
            break;
        }
        case 10:
        {
            testDeviceMove(7);
            break;
        }
        case 11:
        {
            testDeviceMove(8);
            break;
        }
        case 12:
        {
            testDeviceMove(9);
            break;
        }
        case 13:
        {
            testDeviceMove(10);
            break;
        }
        case 14:
        {
            testDeviceSend();
            break;
        }
        case 15:
        {
            testDeviceSendError();
            break;
        }
        default:
        {
            printColoredText("Invalid argument", FOREGROUND_RED | FOREGROUND_INTENSITY);
            std::cout << ": unknown test name";
		    return RetCodes::ERR_INVALID_PARAM;
        }
    }

    return 0;
}

void testDeviceConstruct()
{
    UUID uuid;
    (void)UuidCreate(&uuid);
    Coord coord = randomCoordInSpb();

    Device device(uuid, coord);

    assert(uuid == device.getId());
    assert(coord.lat_ == device.getCoord().lat_);
    assert(coord.lon_ == device.getCoord().lon_);
}

void testDeviceCopyConstruct()
{
    UUID uuid;
    (void)UuidCreate(&uuid);
    Coord coord = randomCoordInSpb();

    Device device1(uuid, coord);

    Device device2(device1);

    assert(device1.getId() == device2.getId());
    assert(device1.getCoord().lat_ == device2.getCoord().lat_);
    assert(device1.getCoord().lon_ == device2.getCoord().lon_);
}

void testDeviceMove(int choice)
{
    UUID uuid;
    (void)UuidCreate(&uuid);
    Coord coord;

    coord.lat_ = (MAX_LAT + MIN_LAT) / 2;
    coord.lon_ = (MAX_LON + MIN_LON) / 2;

    switch (choice)
    {
    case 0:
    case 4:
    {
        Device device(uuid, coord);
        device.move(static_cast<Direction>(choice));
        assert(abs(coord.lat_ - device.getCoord().lat_) > DEVICE_STEP ||
               abs(coord.lon_ - device.getCoord().lon_) < DEVICE_STEP);
        break;
    }
    case 1:
    case 3:
    case 5:
    case 7:
    {
        Device device(uuid, coord);
        device.move(static_cast<Direction>(choice));
        assert(abs(coord.lat_ - device.getCoord().lat_) > DEVICE_STEP ||
               abs(coord.lon_ - device.getCoord().lon_) > DEVICE_STEP);
        break;
    }
    case 2:
    case 6:
    {
        Device device(uuid, coord);
        device.move(static_cast<Direction>(choice));
        assert(abs(coord.lat_ - device.getCoord().lat_) < DEVICE_STEP ||
               abs(coord.lon_ - device.getCoord().lon_) > DEVICE_STEP);
        break;
    }
    case 8:
    {
        coord.lat_ = (MAX_LAT + MIN_LAT) / 2;
        coord.lon_ = (MAX_LON + MIN_LON) / 2;
        Device device(uuid, coord);

        RetCodes rc = device.move(static_cast<Direction>(choice));
        assert(rc == RetCodes::ERR_UNKNOWN_DESTINATION);
    }
    case 9:
    {
        coord.lat_ = MAX_LAT;
        coord.lon_ = (MAX_LON - MIN_LON) / 2;
        Device device(uuid, coord);

        device.move(Direction::NORTH);
        assert(abs(coord.lat_ - device.getCoord().lat_) <= DEVICE_STEP);
    }
    case 10:
    {
        coord.lat_ = (MAX_LAT - MIN_LAT) / 2;
        coord.lon_ = MAX_LON;
        Device device(uuid, coord);

        device.move(Direction::EAST);
        assert(abs(coord.lon_ - device.getCoord().lon_) <= DEVICE_STEP);
    }
    default:
        break;
    }
}

void testDeviceSend()
{
    UUID uuid;
    (void)UuidCreate(&uuid);
    Coord coord = randomCoordInSpb();

    Device device(uuid, coord);

    RetCodes rc = device.send("http://localhost:8088/add/coordinate");
    assert(rc == RetCodes::SUCCESS);
}

void testDeviceSendError()
{
    UUID uuid;
    (void)UuidCreate(&uuid);
    Coord coord = randomCoordInSpb();

    Device device(uuid, coord);

    RetCodes rc = device.send("http://asdasd");
    assert(rc == RetCodes::ERR_URL_CONECTION);
}