#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "Utils.hpp"
#include <uuid/uuid.h>

class Device
{
public:

	Device() = delete;

	Device(uuid_t& uuid, Coord coord);
	Device(const Device &device);

	~Device() = default;

	void  setCoord(Coord newCoord);
	Coord getCoord();
	uuid_t& getId();
	std::string getIdString();

	RetCodes move(Direction dir);
	RetCodes send(std::string url);

	void printDevice();

private:

	uuid_t uuid;
	Coord coord;
};

struct DeviceVector
{
	std::vector<Device> devices;
	std::string 		newDevicesUuid;
	int 				deviceCount = 0;

	void initDevices(std::string fileName);
	void updateConfig(std::string fileName);
};

#endif
