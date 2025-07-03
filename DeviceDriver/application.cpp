#include "application.h"
#include <iostream>
Application::Application(DeviceDriver* driver) : driver{driver}
{
}

void Application::readAndPrint(int start, int end)
{
	std::cout << "\nprint Values (" << start << " ~ " << end << ")\n";
	for (int addr = start; addr < end; ++addr) {
		int data = driver->read(addr);
		std::cout << addr << " : " << data << "\n";
	}
}
