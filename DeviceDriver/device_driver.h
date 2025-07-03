#pragma once
#include "flash_memory_device.h"
#include "exception"

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

class ReadFailException : public std::exception {
public:
    ReadFailException() = default;
    virtual const char* what() const override;
};


class WriteFailException : public std::exception {
public:
    WriteFailException() = default;
    virtual const char* what() const override;
};
