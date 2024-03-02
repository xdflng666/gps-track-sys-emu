#include "Utils.hpp"

#include <iostream>
#include <random>

void printColoredText(const char* text, int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	std::cout << text;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

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
		printColoredText("Invalid argument", FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << ": specify the number of devices to emulate and POST URL";
		return RetCodes::ERR_INVALID_PARAM;
	}

	int tempDeviceCount = atoi(argv[1]);

	if (tempDeviceCount <= 0)
	{
		printColoredText("Invalid argument", FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << ": the number of devices must be positive";
		return RetCodes::ERR_NEGATIVE_VALUE;
	}
	deviceCount = tempDeviceCount;

	std::string tempUrl = argv[2];
	if (tempUrl.find("http://") == url.npos)
	{
		printColoredText("Invalid argument", FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << ": POST URL must have format 'http://...'";
		return RetCodes::ERR_INVALID_URL;
	}
	url = tempUrl;

	return RetCodes::SUCCESS;
}
