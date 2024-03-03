#include <iostream>
#include <vector>
#include <string>

#include <ctime>
#include <chrono>
#include <unistd.h>

#include <fstream>

#include "Device.hpp"
#include "Utils.hpp"

int main(int argc, char* argv[])
{
	// =============================
	//  Проверка входных параметров
	// =============================
	int deviceCount = 0;
	std::string url;
	RetCodes rc = checkEnterParams(argc, argv, deviceCount, url);
	if (rc != RetCodes::SUCCESS)
	{
		return rc;
	}

	srand(time(NULL));

	// =========================
	//  Инициализация устройств
	// =========================
	DeviceVector deviceVector;
	deviceVector.deviceCount = deviceCount;

	std::cout << "  ----INITIALIZATION----  " << std::endl << std::endl;
	deviceVector.initDevices("config.txt");
	std::cout << "  ----------------------  " << std::endl << std::endl;

	// ===================================
	//  Запись использованных UUID в файл
	// ===================================
	deviceVector.updateConfig("config.txt");

	std::cout << "  -------EMULATION------  " << std::endl << std::endl;

	// ====================
	//  Эмуляция устройств
	// ====================
	while (true)
	{
		std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::cout << "\033[1;32m" << std::ctime(&time) << "\033[0m\n";
		for (int i = 0; i < deviceCount; i++)
		{
			Direction direction = static_cast<Direction>(std::rand() % 8);
			deviceVector.devices[i].move(direction);

			std::cout << "\033[1;34m    ==Device " << std::to_string(i + 1) << "==    \033[0m\n";
			deviceVector.devices[i].printDevice();

			deviceVector.devices[i].send(url /*"http://localhost:8088/add/coordinate"*/);
		}
		std::cout << "  ~~~~~~~~~~~~~~~~~~~~~~  " << std::endl << std::endl;
		sleep(60);
	}

	return 0;
}
