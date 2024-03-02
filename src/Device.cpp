#include "Device.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>

#include "Utils.hpp"

#define SHOW_REQUEST
#define SHOW_RESPONSE

Device::Device(UUID id, Coord coord) :
	id(id)
{
	this->coord.lat_ = coord.lat_;
	this->coord.lon_ = coord.lon_;
}

Device::Device(const Device& device) :
	id(device.id),
	coord(device.coord)
{ }

void  Device::setCoord(Coord newCoord)
{
	coord = newCoord;
}

Coord Device::getCoord()
{
	return coord;
}

UUID  Device::getId()
{
	return id;
}

std::string Device::getIdString()
{
	std::string temp;
	RPC_CSTR rpcUuid = NULL;
	(void)UuidToStringA(&id, &rpcUuid);
	temp = (char*)rpcUuid;

	RpcStringFreeA(&rpcUuid);
	
	return temp;
}

RetCodes Device::move(Direction dir)
{
	Coord lastCoord = coord;

	switch (dir)
	{
	case NORTH:
		coord.lat_ += DEVICE_STEP;
		break;
	case NORTHEAST:
		coord.lat_ += DEVICE_STEP;
		coord.lon_ += DEVICE_STEP;
		break;
	case EAST:
		coord.lon_ += DEVICE_STEP;
		break;
	case SOUTHEAST:
		coord.lat_ -= DEVICE_STEP;
		coord.lon_ += DEVICE_STEP;
		break;
	case SOUTH:
		coord.lat_ -= DEVICE_STEP;
		break;
	case SOUTHWEST:
		coord.lat_ -= DEVICE_STEP;
		coord.lon_ -= DEVICE_STEP;
		break;
	case WEST:
		coord.lon_ -= DEVICE_STEP;
		break;
	case NORTHWEST:
		coord.lat_ += DEVICE_STEP;
		coord.lon_ -= DEVICE_STEP;
		break;
	default:
		std::cout << "Error: Unknown destination";
		return RetCodes::ERR_UNKNOWN_DESTINATION;
	}

	if (coord.lat_ < MIN_LAT || coord.lat_ > MAX_LAT)
	{
		coord.lat_ = lastCoord.lat_;
	}
	if (coord.lat_ < MIN_LON || coord.lon_ > MAX_LON)
	{
		coord.lon_ = lastCoord.lon_;
	}

	return RetCodes::SUCCESS;
}

RetCodes Device::send(std::string url)
{
	try
	{
		http::Request request{ url };

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

		return RetCodes::SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Request failed, error: " << e.what() << '\n';
		return RetCodes::ERR_URL_CONECTION;
	}
}

void Device::printDevice()
{
	std::string uuid = getIdString();

	std::cout << "  UUID:  " << uuid << std::endl
			  << "  Coord: LAT: " << std::fixed << std::setprecision(6)<< coord.lat_ << std::endl
			  << "         LON: " << coord.lon_ << std::endl << std::endl;
}

void DeviceVector::initDevices(std::string fileName)
{
	std::ifstream fileIn(fileName);
	for (int i = 0; i < deviceCount; i++)
	{
		UUID uuid;
		std::string fileUuid;
		std::getline(fileIn, fileUuid);
		if (fileIn.fail())
		{
			(void)UuidCreate(&uuid);

			std::string temp;
			RPC_CSTR rpcUuid = NULL;
			(void)UuidToStringA(&uuid, &rpcUuid);
			temp = (char*)rpcUuid;

			newDevicesUuid.append(temp);
			newDevicesUuid.append("\n");
		}
		else
		{
			(void)UuidFromStringA((RPC_CSTR)fileUuid.data(), &uuid);
		}

		Coord coord		 = randomCoordInSpb();
		Device newDevcie = Device(uuid, coord);

		devices.push_back(newDevcie);

		std::string deviceTopic = "    ==Device " + std::to_string(i+1) + "==    \n";
		printColoredText(deviceTopic.data(), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		devices[i].printDevice();
	}
	fileIn.close();
}

void DeviceVector::updateConfig(std::string fileName)
{
	if (!newDevicesUuid.empty())
	{
		std::ofstream fileOut("config.txt", std::ios_base::app);
		fileOut << newDevicesUuid;
		fileOut.close();
	}
}
