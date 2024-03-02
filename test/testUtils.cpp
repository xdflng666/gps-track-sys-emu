#include <iostream>
#include <cassert>
#include <fstream>

#include "Device.hpp"
#include "Utils.hpp"

std::map<std::string, int> tests = { { "testUtilsCheckEnterParamsInvalidPeram",  1 },
                                     { "testUtilsCheckEnterParamsNegativeValue", 2 },
                                     { "testUtilsCheckEnterParamsInvalidUrl",    3 },
                                     { "testUtilsCheckEnterParamsSuccess",        4 },
                                     { "testUtilsCheckEnterParamsSuccessValue",   5 },
                                     { "testUtilsRandomCoordInSpb",              6 } };


void testUtilsCheckEnterParamsInvalidPeram();
void testUtilsCheckEnterParamsNegativeValue();
void testUtilsCheckEnterParamsInvalidUrl();
void testUtilsCheckEnterParamsSuccess();
void testUtilsCheckEnterParamsSuccessValue();
void testUtilsRandomCoordInSpb();

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
            testUtilsCheckEnterParamsInvalidPeram();
            break;
        }
        case 2:
        {
            testUtilsCheckEnterParamsNegativeValue();
            break;
        }
        case 3:
        {
            testUtilsCheckEnterParamsInvalidUrl();
            break;
        }
        case 4:
        {
            testUtilsCheckEnterParamsSuccess();
            break;
        }
        case 5:
        {
            testUtilsCheckEnterParamsSuccessValue();
            break;
        }
        case 6:
        {
            testUtilsRandomCoordInSpb();
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

void testUtilsCheckEnterParamsInvalidPeram()
{
    int deviceCount = 0;
    std::string url;
    RetCodes rc = checkEnterParams(2, nullptr, deviceCount, url);

    assert(rc == RetCodes::ERR_INVALID_PARAM);
}

void testUtilsCheckEnterParamsNegativeValue()
{
    int deviceCount = 0;
    std::string url;
    char* argv[3] = { (char*)"3", (char*)"-2", (char*)"http://google.com"};
    RetCodes rc = checkEnterParams(3, argv, deviceCount, url);

    assert(rc == RetCodes::ERR_NEGATIVE_VALUE);
}

void testUtilsCheckEnterParamsInvalidUrl()
{
    int deviceCount = 0;
    std::string url;
    char* argv[3] = {(char*)"3", (char*)"2", (char*)"google.com"};
    RetCodes rc = checkEnterParams(3, argv, deviceCount, url);

    assert(rc == RetCodes::ERR_INVALID_URL);
}

void testUtilsCheckEnterParamsSuccess()
{
    int deviceCount = 0;
    std::string url;
    char* argv[3] = {(char*)"3", (char*)"2", (char*)"http://google.com" };
    RetCodes rc = checkEnterParams(3, argv, deviceCount, url);

    assert(rc == RetCodes::SUCCESS);
}

void testUtilsCheckEnterParamsSuccessValue()
{
    int deviceCount = 0;
    std::string url;
    char* argv[3] = {(char*)"3", (char*)"2", (char*)"http://google.com" };
    RetCodes rc = checkEnterParams(3, argv, deviceCount, url);

    assert(rc == RetCodes::SUCCESS && deviceCount == 2 && url.compare("http://google.com") == 0);
}

void testUtilsRandomCoordInSpb()
{
    Coord coord1 = randomCoordInSpb();
    Coord coord2 = randomCoordInSpb();
    Coord coord3 = randomCoordInSpb();
    Coord coord4 = randomCoordInSpb();
    Coord coord5 = randomCoordInSpb();

    assert(coord1.lat_ >= MIN_LAT && coord1.lat_ <= MAX_LAT &&
           coord1.lon_ >= MIN_LON && coord1.lon_ <= MAX_LON);
    assert(coord2.lat_ >= MIN_LAT && coord2.lat_ <= MAX_LAT &&
           coord2.lon_ >= MIN_LON && coord2.lon_ <= MAX_LON);
    assert(coord3.lat_ >= MIN_LAT && coord3.lat_ <= MAX_LAT &&
           coord3.lon_ >= MIN_LON && coord3.lon_ <= MAX_LON);
    assert(coord4.lat_ >= MIN_LAT && coord4.lat_ <= MAX_LAT &&
           coord4.lon_ >= MIN_LON && coord4.lon_ <= MAX_LON);
    assert(coord5.lat_ >= MIN_LAT && coord5.lat_ <= MAX_LAT &&
           coord5.lon_ >= MIN_LON && coord5.lon_ <= MAX_LON);
}

