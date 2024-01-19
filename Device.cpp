#include "Device.hpp"

#include <iostream>
#include <iomanip>

#include "Utils.hpp"

#define SHOW_REQUEST
#define SHOW_RESPONSE

Device::Device(UUID id, Coord coord) :
	id(id),
	coord(coord)
{ }

Device::Device(const Device& device) :
	id(device.id),
	coord(device.coord)
{ }

std::string Device::getIdString()
{
	std::string temp;
	RPC_CSTR rpcUuid = NULL;
	(void)UuidToStringA(&id, &rpcUuid);
	temp = (char*)rpcUuid;
	
	return temp;
}

void Device::move()
{
	int direction = std::rand() % 8;
	Coord lastCoord = coord;

	switch (direction)
	{
	case NORTH:
		coord.lat_ += DEVISE_STEP;
		break;
	case NORTHEAST:
		coord.lat_ += DEVISE_STEP;
		coord.lon_ += DEVISE_STEP;
		break;
	case EAST:
		coord.lon_ += DEVISE_STEP;
		break;
	case SOUTHEAST:
		coord.lat_ -= DEVISE_STEP;
		coord.lon_ += DEVISE_STEP;
		break;
	case SOUTH:
		coord.lat_ -= DEVISE_STEP;
		break;
	case SOUTHWEST:
		coord.lat_ -= DEVISE_STEP;
		coord.lon_ -= DEVISE_STEP;
		break;
	case WEST:
		coord.lon_ -= DEVISE_STEP;
		break;
	case NORTHWEST:
		coord.lat_ += DEVISE_STEP;
		coord.lon_ -= DEVISE_STEP;
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

void Device::send()
{
	try
	{
		http::Request request{ "http://localhost:8088/add/coordinate" };

		const std::string body = "{\"device_id\": \"" + getIdString() + "\", \"coordinates\": {\"latitude\": " +
								 std::to_string(coord.lat_) + ", \"longitude\": " + std::to_string(coord.lon_) + "}}";

#ifdef SHOW_REQUEST
		printColoredText("   Request:", FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << std::endl << body << std::endl << std::endl;
#endif

		const auto response = request.send("POST", body, {
			{"Content-Type", "application/json"}
		});

#ifdef SHOW_RESPONSE
		printColoredText("   Response:", FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		std::cout << std::endl << std::string{response.body.begin(), response.body.end()} << std::endl;
#endif
	}
	catch (const std::exception& e)
	{
		std::cerr << "Request failed, error: " << e.what() << '\n';
		return;
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
