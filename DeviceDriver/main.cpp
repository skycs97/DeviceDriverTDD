#include "gmock/gmock.h"
#include "device_driver.h"

using namespace testing;

class FlashMemoryDeviceMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long, unsigned char), (override));
};

TEST(DeviceDriver, ReadFromHW) {
	// TODO : replace hardware with a Test Double
	FlashMemoryDeviceMock hardware;
	DeviceDriver driver{ &hardware };

	EXPECT_CALL(hardware, read(0xFF))
		.WillRepeatedly(Return(0x41));

	int data = driver.read(0xFF);
	EXPECT_EQ(0x41, data);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}