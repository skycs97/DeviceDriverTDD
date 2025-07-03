#pragma once
#include "flash_memory_device.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
private:
    constexpr static int READ_REPEAT_COUNT_FOR_CHECK = 4;
};