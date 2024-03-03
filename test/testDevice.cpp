#include <iostream>
#include <cassert>
#include <fstream>

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
                                     { "testDeviceSendError",     15 },
                                     { "testDeviceInitDevices",   16 },  
                                     { "testDeviceSeveralInit",   17 },
                                     { "testDeviceSetCoord",      18 },
                                     { "testDeviceGetIdString",   19 }};

void testDeviceConstruct();
void testDeviceCopyConstruct();
void testDeviceMove(int choice);
void testDeviceSend();
void testDeviceSendError();
void testDeviceInitDevices(int deviceCount);
void testDeviceSeveralInit();
void testDeviceSetCoord();
void testDeviceGetIdString();

int main(int argc, char* argv[])
{
    int choice = 0;

    if (argc != 2)
    {
        std::cout << "\033[1;31m Invalid argument\033[0m" << ": specify the name of test";
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
        case 16:
        {
            testDeviceInitDevices(5);
            break;
        }
        case 17:
        {
            testDeviceSeveralInit();
            break;
        }
        case 18:
        {
            testDeviceSetCoord();
            break;
        }
        case 19:
        {
            testDeviceGetIdString();
            break;
        }
        default:
        {
            std::cout << "\033[1;31m Invalid argument\033[0m" << ": unknown test name";
		    return RetCodes::ERR_INVALID_PARAM;
        }
    }

    return 0;
}

void testDeviceConstruct()
{
    uuid_t uuid;
    uuid_generate(uuid);
    Coord coord = randomCoordInSpb();

    Device device(uuid, coord);

    assert(uuid_compare(uuid, device.getId()) == 0);
    assert(coord.lat_ == device.getCoord().lat_);
    assert(coord.lon_ == device.getCoord().lon_);
}

void testDeviceCopyConstruct()
{
    uuid_t uuid;
    uuid_generate(uuid);
    Coord coord = randomCoordInSpb();

    Device device1(uuid, coord);

    Device device2(device1);

    assert(uuid_compare(device1.getId(), device2.getId()) == 0);
    assert(device1.getCoord().lat_ == device2.getCoord().lat_);
    assert(device1.getCoord().lon_ == device2.getCoord().lon_);
}

void testDeviceMove(int choice)
{
    uuid_t uuid;
    uuid_generate(uuid);
    Coord coord;

    switch (choice)
    {
    case 0:
    case 4:
    {
        coord.lat_ = (MAX_LAT + MIN_LAT) / 2;
        coord.lon_ = (MAX_LON + MIN_LON) / 2;
        Device device(uuid, coord);
        device.move(static_cast<Direction>(choice));
        assert(abs(coord.lat_ - device.getCoord().lat_) > 0.00001 ||
               abs(coord.lon_ - device.getCoord().lon_) < 0.00001);
        break;
    }
    case 1:
    case 3:
    case 5:
    case 7:
    {
        coord.lat_ = (MAX_LAT + MIN_LAT) / 2;
        coord.lon_ = (MAX_LON + MIN_LON) / 2;
        Device device(uuid, coord);
        std::cout << "coord.lat_ = " << device.getCoord().lat_ << std::endl;
        std::cout << "coord.lon_ = " << device.getCoord().lon_ << std::endl;
        device.move(static_cast<Direction>(choice));
        std::cout << "coord.lat_ = " << device.getCoord().lat_ << std::endl;
        std::cout << "coord.lon_ = " << device.getCoord().lon_ << std::endl;
        assert(abs(coord.lat_ - device.getCoord().lat_) < 0.00001 ||
               abs(coord.lon_ - device.getCoord().lon_) < 0.00001);
        break;
    }
    case 2:
    case 6:
    {
        coord.lat_ = (MAX_LAT + MIN_LAT) / 2;
        coord.lon_ = (MAX_LON + MIN_LON) / 2;
        Device device(uuid, coord);
        device.move(static_cast<Direction>(choice));
        assert(abs(coord.lat_ - device.getCoord().lat_) < 0.00001 ||
               abs(coord.lon_ - device.getCoord().lon_) > 0.00001);
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
        assert(abs(coord.lat_ - device.getCoord().lat_) <= 0.00001);
    }
    case 10:
    {
        coord.lat_ = (MAX_LAT - MIN_LAT) / 2;
        coord.lon_ = MAX_LON;
        Device device(uuid, coord);

        device.move(Direction::EAST);
        assert(abs(coord.lon_ - device.getCoord().lon_) <= 0.00001);
    }
    default:
        break;
    }
}

void testDeviceSend()
{
    uuid_t uuid;
    uuid_generate(uuid);
    Coord coord = randomCoordInSpb();

    Device device(uuid, coord);

    RetCodes rc = device.send("http://google.com");
    assert(rc == RetCodes::SUCCESS);
}

void testDeviceSendError()
{
    uuid_t uuid;
    uuid_generate(uuid);
    Coord coord = randomCoordInSpb();

    Device device(uuid, coord);

    RetCodes rc = device.send("http://asdasd");
    assert(rc == RetCodes::ERR_URL_CONECTION);
}

void testDeviceInitDevices(int deviceCount)
{
    DeviceVector deviceVector;
	deviceVector.deviceCount = deviceCount;

    deviceVector.initDevices("test.txt");
    deviceVector.updateConfig("test.txt");

    std::ifstream file("test.txt");
    int counter = 0;

    while (!file.eof())
    {
        ++counter;
        char str[1024];
        file.getline(str, 1024, '\n');
    }
    file.close();
    remove("test.txt");

    std::cout << counter << std::endl;

    assert(counter-1 == deviceCount);
}

void testDeviceSeveralInit()
{
    DeviceVector deviceVector;
	deviceVector.deviceCount = 5;

    deviceVector.initDevices("test.txt");
    deviceVector.updateConfig("test.txt");

    DeviceVector deviceVector2;
    deviceVector2.deviceCount = 3;

    deviceVector2.initDevices("test.txt");
    deviceVector2.updateConfig("test.txt");

    std::ifstream file("test.txt");
    int counter = 0;

    while (!file.eof())
    {
        ++counter;
        char str[1024];
        file.getline(str, 1024, '\n');
    }
    file.close();
    remove("test.txt");

    std::cout << counter << std::endl;

    assert(counter-1 == 5);
}

void testDeviceSetCoord()
{
    uuid_t uuid;
    uuid_generate(uuid);
    Coord coord1 = randomCoordInSpb();
    Coord coord2 = randomCoordInSpb();

    Device device(uuid, coord1);
    device.setCoord(coord2);

    assert(abs(device.getCoord().lat_ - coord2.lat_) < 0.00001 &&
           abs(device.getCoord().lon_ - coord2.lon_) < 0.00001);
}

void testDeviceGetIdString()
{
    uuid_t uuid;
    uuid_generate(uuid);
    Coord coord = randomCoordInSpb();
    Device device(uuid, coord);

    std::string uuidString = device.getIdString();
    uuid_t uuid2;
    uuid_parse(uuidString.c_str(), uuid2);

    assert(uuid_compare(uuid, uuid2) == 0);
}
