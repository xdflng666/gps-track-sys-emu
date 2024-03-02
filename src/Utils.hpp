#ifndef UTILS_HPP
#define UTILS_HPP

#include "HTTPRequest.hpp"

const double MIN_LAT = 59.7006;
const double MAX_LAT = 60.1269;
const double MIN_LON = 30.1376;
const double MAX_LON = 30.5174;

const double DEVICE_STEP = 0.0001;

enum Direction : int
{
	NORTH = 0,
	NORTHEAST,
	EAST,
	SOUTHEAST,
	SOUTH,
	SOUTHWEST,
	WEST,
	NORTHWEST
};

enum RetCodes : int
{
	SUCCESS = 0,

	ERR_INVALID_PARAM,
	ERR_NEGATIVE_VALUE,
	ERR_INVALID_URL,
	ERR_URL_CONECTION,
	ERR_UNKNOWN_DESTINATION
};

struct Coord
{
	double lat_ = 0;
	double lon_ = 0;
};

Coord randomCoordInSpb();

RetCodes checkEnterParams(int argc, char* argv[], int& deviceCount, std::string& url);

#endif