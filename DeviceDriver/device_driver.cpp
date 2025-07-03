#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    int data = (int)(m_hardware->read(address));
    int before = data;

    for (int i = 0; i < READ_REPEAT_COUNT_FOR_CHECK; ++i) {
        data = (int)(m_hardware->read(address));
        if (before != data) {
            throw ReadFailException();
        }
        before = data;
    }

    return data;
}

void DeviceDriver::write(long address, int data)
{
    int readVal = read(address);

    m_hardware->write(address, (unsigned char)data);
}

const char* ReadFailException::what() const
{
    return "data is invalid";
}
