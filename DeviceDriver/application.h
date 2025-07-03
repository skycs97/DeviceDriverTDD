#pragma once
#include "device_driver.h"

class Application {
public:
	Application(DeviceDriver* driver);
	void readAndPrint(int start, int end);
private:
	DeviceDriver* driver;
public:
};