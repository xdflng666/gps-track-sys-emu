#include <iostream>
#include <vector>
#include <string>

#include <ctime>
#include <chrono>

#include <fstream>

#pragma comment(lib, "rpcrt4.lib")
#pragma comment(lib, "ws2_32.lib")
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
		printColoredText(std::ctime(&time), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		for (int i = 0; i < deviceCount; i++)
		{
			Direction direction = static_cast<Direction>(std::rand() % 8);
			deviceVector.devices[i].move(direction);

			std::string deviceTopic = "    ==Device " + std::to_string(i + 1) + "==    \n";
			printColoredText(deviceTopic.data(), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			deviceVector.devices[i].printDevice();

			deviceVector.devices[i].send(url /*"http://localhost:8088/add/coordinate"*/);
		}
		std::cout << "  ~~~~~~~~~~~~~~~~~~~~~~  " << std::endl << std::endl;
		Sleep(60 * 1000);
	}

	return 0;
}
