#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class FlashMemoryDeviceMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

class DeviceDriverFixture : public Test {
public:
	DeviceDriverFixture() : driver{ &hardware } {

	}
	void readTest(int expected, int address) {
		int data = driver.read(address);
		EXPECT_EQ(expected, data);
	}
	void readFailTest(int expected, int address) {
		try {
			readTest(expected, address);
			FAIL();
		}
		catch (ReadFailException& e) {
			EXPECT_EQ("data is invalid", e.what());
		}
	}

	void setReadSuccessCase(int value, int address) {
		EXPECT_CALL(hardware, read(address))
			.Times(5)
			.WillRepeatedly(Return(value));
	}

	void writeTest(int writeValue, int address) {
		setReadSuccessCase(EMPTY_DATA, address);
		driver.write(address, writeValue);

		setReadSuccessCase(writeValue, address);
		readTest(writeValue, address);
	}

	void writeFailTest(int writeValue, int address) {
		try {
			setReadSuccessCase(0x10, address);
			driver.write(address, writeValue);

			setReadSuccessCase(writeValue, address);
			readTest(writeValue, address);
		}
		catch (WriteFailException& e) {
			EXPECT_EQ("already writed data", e.what());
		}
	}

	NiceMock<FlashMemoryDeviceMock> hardware;
	DeviceDriver driver;

	constexpr static int EMPTY_DATA = 0xFF;
};

TEST_F(DeviceDriverFixture, ReadFromHW_0x00_0x41) {
	int address = 0x00;
	int expected = 0x41;

	setReadSuccessCase(expected, address);

	readTest(expected, address);
}

TEST_F(DeviceDriverFixture, ReadFromHW_0x04_0x42) {
	int address = 0x04;
	int expected = 0x42;

	setReadSuccessCase(expected, address);

	readTest(expected, address);
}

TEST_F(DeviceDriverFixture, ReadFromHW_Fail) {
	int address = 0x04;
	int expected = 0x42;
	int invalidData = 0x41;

	EXPECT_CALL(hardware, read(address))
		.WillOnce(Return(invalidData))
		.WillRepeatedly(Return(expected));

	readFailTest(expected, address);
}

TEST_F(DeviceDriverFixture, WriteToHw) {
	int address = 0x00;
	int writeValue = 0x4;

	writeTest(writeValue, address);
}

TEST_F(DeviceDriverFixture, WriteToHw_Fail_Already_Writed_Data) {
	int address = 0x00;
	int writeValue = 0x4;

	writeFailTest(writeValue, address);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}