#include "application.h"
#include <iostream>
Application::Application(DeviceDriver* driver) : driver{driver}
{
}

void Application::readAndPrint(int startAddr, int endAddr)
{
	std::cout << "\nprint Values (" << startAddr << " ~ " << endAddr << ")\n";

	for (int addr = startAddr; addr < endAddr; ++addr) {
		int data = driver->read(addr);
		printData(addr, data);
	}
}

void Application::printData(int addr, int data)
{
	std::cout << addr << " : " << data << "\n";
}

void Application::writeAll(int writeValue)
{
	constexpr static int writeAllStartAddr = 0x0;
	constexpr static int writeAllEndAddr = 0x4;
	for (int i = writeAllStartAddr; i < writeAllEndAddr; ++i) {
		driver->write(i, writeValue);
	}
}
