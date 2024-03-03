#include "Utils.hpp"

#include <iostream>
#include <random>

Coord randomCoordInSpb()
{
	Coord newCoord;

	std::uniform_real_distribution<double> unifLat(MIN_LAT, MAX_LAT);
	std::uniform_real_distribution<double> unifLon(MIN_LON, MAX_LON);
	std::random_device rd;
	std::default_random_engine re(rd());

	newCoord.lat_ = unifLat(re);
	newCoord.lon_ = unifLon(re);

	return newCoord;
}

RetCodes checkEnterParams(int argc, char* argv[], int& deviceCount, std::string& url)
{
	if (argc != 3)
	{
		std::cout << "\033[1;31mInvalid argument\033[0m" << ": specify the number of devices to emulate and POST URL\n";
		return RetCodes::ERR_INVALID_PARAM;
	}

	int tempDeviceCount = atoi(argv[1]);

	if (tempDeviceCount <= 0)
	{
		std::cout << "\033[1;31mInvalid argument\033[0m" << ": the number of devices must be positive\n";
		return RetCodes::ERR_NEGATIVE_VALUE;
	}
	deviceCount = tempDeviceCount;

	std::string tempUrl = argv[2];
	if (tempUrl.find("http://") == url.npos)
	{
		std::cout << "\033[1;31mInvalid argument\033[0m" << ": POST URL must have format 'http://...'\n";
		return RetCodes::ERR_INVALID_URL;
	}
	url = tempUrl;

	return RetCodes::SUCCESS;
}
