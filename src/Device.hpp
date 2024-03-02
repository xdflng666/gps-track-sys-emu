#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "Utils.hpp"

class Device
{
public:

	Device() = delete;

	Device(UUID id, Coord coord);
	Device(const Device &device);

	~Device() = default;

	void  setCoord(Coord newCoord);
	Coord getCoord();
	UUID  getId();
	std::string getIdString();

	RetCodes move(Direction dir);
	RetCodes send(std::string url);

	void printDevice();

private:

	UUID  id;
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
