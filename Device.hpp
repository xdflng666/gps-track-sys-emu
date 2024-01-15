#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include <windows.h>

const double MIN_LAT = 59.7006;
const double MAX_LAT = 60.1269;
const double MIN_LON = 30.1376;
const double MAX_LON = 30.5174;

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

struct Coord
{
	double lat_ = 0;
	double lon_ = 0;
};

class Device
{
public:

	Device() = delete;

	Device(UUID id, Coord coord);
	Device(const Device &device);

	~Device() = default;

	UUID&  getId();
	Coord getCoord();
	void  setCoord(Coord newCoord);

	void move();

	void printDevice(int number);

private:

	UUID  id;
	Coord coord;
};

#endif
