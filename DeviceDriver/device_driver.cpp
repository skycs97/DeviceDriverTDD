#include "device_driver.h"
#include "exception"

class ReadFailException : public std::exception {
public:
    ReadFailException(const char* const Msg) : std::exception{Msg}{}
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{
}

int DeviceDriver::read(long address)
{
    int data = (int)(m_hardware->read(address));
    int before = data;

    for (int i = 0; i < READ_REPEAT_COUNT_FOR_CHECK; ++i) {
        if (before != data) {
            throw ReadFailException("data is invalid");
        }
    }

    return data;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}