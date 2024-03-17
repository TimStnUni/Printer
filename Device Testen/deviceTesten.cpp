#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;

#include "../Printer.h"

using namespace System;

class DeviceTests : public ::testing::Test {
protected:
    Device device;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

// Test constructor met geldige waarden
TEST_F(DeviceTests, ConstructorWithValidValues) {
Device tempDevice("Printer1", 50, 20);
ASSERT_EQ(tempDevice.getNameDev(), "Printer1");
ASSERT_EQ(tempDevice.getEmissions(), 50);
ASSERT_EQ(tempDevice.getSpeed(), 20);
}

// Test constructor met ongeldige waarden
TEST_F(DeviceTests, ConstructorWithInvalidEmissions) {
EXPECT_ANY_THROW(Device tempDevice("Printer1", -10, 20));
}

// Test setNameDev methode met geldige en ongeldige waarden
TEST_F(DeviceTests, SetNameDevValidAndInvalid) {
device.setNameDev("Printer2");
ASSERT_EQ(device.getNameDev(), "Printer2");
s
// Verwacht dat een lege string niet toegestaan is
EXPECT_ANY_THROW(device.setNameDev(""));
}

// Test setEmissions methode met een neg waarde
TEST_F(DeviceTests, SetEmissionsWithNegativeValue) {
EXPECT_ANY_THROW(device.setEmissions(-1));
}

// Test setSpeed methode met een neg waarde
TEST_F(DeviceTests, SetSpeedWithNegativeValue) {
EXPECT_ANY_THROW(device.setSpeed(-1));
}
