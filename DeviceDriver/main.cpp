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

	FlashMemoryDeviceMock hardware;
	DeviceDriver driver;
};

TEST_F(DeviceDriverFixture, ReadFromHW_0x00_0x41) {
	int address = 0x00;
	int expected = 0x41;

	EXPECT_CALL(hardware, read(address))
		.WillRepeatedly(Return(expected));

	readTest(expected, address);
}

TEST_F(DeviceDriverFixture, ReadFromHW_0x04_0x42) {
	int address = 0x04;
	int expected = 0x42;

	EXPECT_CALL(hardware, read(address))
		.WillRepeatedly(Return(expected));

	readTest(expected, address);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}