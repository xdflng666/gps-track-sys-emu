#include <iostream>
#include <iomanip>
#include <fstream>

#include "Device.hpp"
#include "Utils.hpp"

// #define SHOW_REQUEST
// #define SHOW_RESPONSE

Device::Device(uuid_t& uuid, Coord coord)
{
	std::copy(uuid, uuid + 16, this->uuid);

	this->coord.lat_ = coord.lat_;
	this->coord.lon_ = coord.lon_;
}

Device::Device(const Device& device) :
	coord(device.coord)
{
	uuid_copy(uuid, device.uuid);
}

void  Device::setCoord(Coord newCoord)
{
	coord = newCoord;
}

Coord Device::getCoord()
{
	return coord;
}

uuid_t& Device::getId()
{
	return uuid;
}

std::string Device::getIdString()
{
	char str[100];
	uuid_unparse(uuid, str);
	std::string temp{ str };
	
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
		std::cout << "\033[1;31mRequest\033[0m" << std::endl << body << std::endl << std::endl;
#endif

		const auto response = request.send("POST", body, {
			{"Content-Type", "application/json"}
		}, std::chrono::milliseconds{5000});

#ifdef SHOW_RESPONSE
		std::cout << "\033[1;31mResponse\033[0m"  << std::endl << std::string{response.body.begin(), response.body.end()} << std::endl;
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
		uuid_t uuid;
		std::string fileUuid;
		std::getline(fileIn, fileUuid);
		if (fileIn.fail())
		{
			uuid_generate(uuid);
			char str[100];
			uuid_unparse(uuid, str);
			std::string temp{ str };

			newDevicesUuid.append(temp);
			newDevicesUuid.append("\n");
		}
		else
		{
			std::copy(fileUuid.begin(), fileUuid.end(), uuid);
		}

		Coord coord		 = randomCoordInSpb();
		Device newDevcie = Device(uuid, coord);

		devices.push_back(newDevcie);

		std::cout << "\033[1;34m    ==Device " << std::to_string(i+1) << "==    \033[0m\n";
		devices[i].printDevice();
	}
	fileIn.close();
}

void DeviceVector::updateConfig(std::string fileName)
{
	if (!newDevicesUuid.empty())
	{
		std::ofstream fileOut(fileName, std::ios_base::app);
		fileOut << newDevicesUuid;
		fileOut.close();
	}
}
