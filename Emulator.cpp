#include <iostream>
#include <vector>
#include <string>

#include <ctime>
#include <chrono>

#include <fstream>

#pragma comment(lib, "rpcrt4.lib")
#include "Utils.hpp"
#include "Device.hpp"

int main(int argc, char* argv[])
{
	// =============================
	//  Проверка входных параметров
	// =============================
	if (argc != 2)
	{
		printColoredText("Invalid argument", FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << ": specify the number of devices to emulate";
		return 1;
	}

	int deviceCount = atoi(argv[1]);

	if (deviceCount <= 0)
	{
		printColoredText("Invalid argument", FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << ": the number of devices must be positive";
		return 1;
	}

	srand(time(NULL));

	// =========================
	//  Инициализация устройств
	// =========================
	std::vector<Device> deviceVector;

	std::cout << "  ----INITIALIZATION----  " << std::endl << std::endl;

	std::string newUUID;
	std::ifstream fileIn("config.txt");
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

			newUUID.append(temp);
			newUUID.append("\n");
		}
		else
		{
			(void)UuidFromStringA((RPC_CSTR)fileUuid.data(), &uuid);
		}

		Coord coord		 = randomCoordInSpb();
		Device newDevcie = Device(uuid, coord);

		deviceVector.push_back(newDevcie);

		std::string deviceTopic = "    ==Device " + std::to_string(i+1) + "==    \n";
		printColoredText(deviceTopic.data(), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		deviceVector[i].printDevice(i+1);
	}
	fileIn.close();

	std::cout << "  ----------------------  " << std::endl << std::endl;

	// ===================================
	//  Запись использованных UUID в файл
	// ===================================
	if (!newUUID.empty())
	{
		std::ofstream fileOut("config.txt", std::ios_base::app);
		fileOut << newUUID;
		fileOut.close();
	}

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
			deviceVector[i].move();

			std::string deviceTopic = "    ==Device " + std::to_string(i + 1) + "==    \n";
			printColoredText(deviceTopic.data(), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			deviceVector[i].printDevice(i + 1);
		}
		std::cout << "  ~~~~~~~~~~~~~~~~~~~~~~  " << std::endl << std::endl;
		Sleep(5000);
	}

	return 0;
}
