#include "Utils.hpp"

#include <iostream>
//#include <Windows.h>
#include <random>

void  printColoredText(const char* text, int color)
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