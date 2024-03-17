#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace std;

#include "../Printer.h" // Zorg ervoor dat dit pad overeenkomt met de locatie van je Printer.h bestand
#include "../TicTacToeUtils.h" // Alleen nodig als TicTacToeUtils.h gebruikt wordt in je tests

class DeviceInputTests: public ::testing::Test {
protected:
    friend class Printer;
    friend class Device;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

/**
Tests for name, emissions, and speed from Devices
 */
TEST_F(DeviceInputTests, DeviceNameIsEmpty) {
    ASSERT_TRUE(DirectoryExists("DeviceTests/DevtestInput"));
    ASSERT_TRUE(FileExists("DeviceTests/DevtestInput/emptyDeviceName.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("DeviceTests/DevtestInput/emptyDeviceName.xml"), false);
    // readXML returns false if the device name is empty
}

TEST_F(DeviceInputTests, EmissionsAreNegative) {
    ASSERT_TRUE(DirectoryExists("DeviceTests/DevtestInput"));
    ASSERT_TRUE(FileExists("DeviceTests/DevtestInput/negativeEmissions.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("DeviceTests/DevtestInput/negativeEmissions.xml"), false);
    // readXML returns false if the emissions value is negative
}

TEST_F(DeviceInputTests, SpeedIsNegative) {
    ASSERT_TRUE(DirectoryExists("DeviceTests/DevtestInput"));
    ASSERT_TRUE(FileExists("DeviceTests/DevtestInput/negativeSpeed.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("DeviceTests/DevtestInput/negativeSpeed.xml"), false);
    // readXML returns false if the speed is negative
}

TEST_F(DeviceInputTests, ValidDeviceInput) {
    ASSERT_TRUE(DirectoryExists("DeviceTests/DevtestInput"));
    ASSERT_TRUE(FileExists("DeviceTests/DevtestInput/validDevice.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("DeviceTests/DevtestInput/validDevice.xml"), true);
    // readXML returns true if the XML input for the device is vali
}
