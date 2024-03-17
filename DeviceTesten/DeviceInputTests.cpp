#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace std;

#include "../Printer.h"
#include "../TicTacToeUtils.h"

class DeviceInputTests: public ::testing::Test {
protected:
    friend class Printer;
    friend class Device;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};


TEST_F(DeviceInputTests, DeviceNameIsEmpty) {
    ASSERT_TRUE(DirectoryExists("DeviceTesten/DevtestInput"));
    ASSERT_TRUE(FileExists("DeviceTesten/DevtestInput/emptyDeviceName.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("DeviceTesten/DevtestInput/emptyDeviceName.xml"), false);
    // readXML returns false if the device name is empty
}

TEST_F(DeviceInputTests, EmissionsAreNegative) {
    ASSERT_TRUE(DirectoryExists("DeviceTesten/DevtestInput"));
    ASSERT_TRUE(FileExists("DeviceTesten/DevtestInput/negativeEmissions.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("DeviceTesten/DevtestInput/negativeEmissions.xml"), false);
    // readXML returns false if the emissions value is negative
}

TEST_F(DeviceInputTests, SpeedIsNegative) {
    ASSERT_TRUE(DirectoryExists("DeviceTesten/DevtestInput"));
    ASSERT_TRUE(FileExists("DeviceTesten/DevtestInput/negativeSpeed.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("DeviceTesten/DevtestInput/negativeSpeed.xml"), false);
    // readXML returns false if the speed is negative
}

TEST_F(DeviceInputTests, ValidDeviceInput) {
    ASSERT_TRUE(DirectoryExists("DeviceTesten/DevtestInput"));
    ASSERT_TRUE(FileExists("DeviceTesten/DevtestInput/validDevice.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("DeviceTesten/DevtestInput/validDevice.xml"), true);
    // readXML returns true if the XML input for the device is vali
}
