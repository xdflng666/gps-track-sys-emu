#include "Device.hpp"

#include <iostream>
#include <iomanip>

Device::Device(UUID id, Coord coord) :
	id(id),
	coord(coord)
{ }

Device::Device(const Device& device) :
	id(device.id),
	coord(device.coord)
{ }

UUID& Device::getId()
{
	return this->id;
}

Coord Device::getCoord()
{
	return this->coord;
}

void Device::setCoord(Coord newCoord)
{
	this->coord.lon_ = newCoord.lon_;
	this->coord.lat_ = newCoord.lon_;
}

void Device::move()
{
	int direction = std::rand() % 8;
	Coord lastCoord = coord;

	switch (direction)
	{
	case NORTH:
		coord.lat_ += 0.000001;
		break;
	case NORTHEAST:
		coord.lat_ += 0.000001;
		coord.lon_ += 0.000001;
		break;
	case EAST:
		coord.lon_ += 0.000001;
		break;
	case SOUTHEAST:
		coord.lat_ -= 0.000001;
		coord.lon_ += 0.000001;
		break;
	case SOUTH:
		coord.lat_ -= 0.000001;
		break;
	case SOUTHWEST:
		coord.lat_ -= 0.000001;
		coord.lon_ -= 0.000001;
		break;
	case WEST:
		coord.lon_ -= 0.000001;
		break;
	case NORTHWEST:
		coord.lat_ += 0.000001;
		coord.lon_ -= 0.000001;
		break;
	}

	if (coord.lat_ < MIN_LAT || coord.lat_ > MAX_LAT)
	{
		coord.lat_ = lastCoord.lat_;
	}
	if (coord.lat_ < MIN_LON || coord.lon_ > MAX_LON)
	{
		coord.lon_ = lastCoord.lon_;
	}
}

void Device::printDevice(int number)
{
	std::string uuid;

	RPC_CSTR rpcUuid = NULL;
	(void)UuidToStringA(&id, &rpcUuid);

	uuid = (char*)rpcUuid;

	std::cout << "  UUID:  " << uuid << std::endl
			  << "  Coord: LAT: " << std::fixed << std::setprecision(6)<< coord.lat_ << std::endl
			  << "         LON: " << coord.lon_ << std::endl << std::endl;

	RpcStringFreeA(&rpcUuid);
}
