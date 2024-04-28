//
// Created by alyja on 14/03/2024.
//
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;


#include "../PrinterSystem.h"
#include "../TicTacToeUtils.h"

class InputTests: public ::testing::Test {
protected:
    friend class Printer;
    friend class Device;
    friend class Job;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};


/**
 * Test to see if the check for Device name works correctly and is not empty
 */

TEST_F(InputTests, DeviceNameIsEmpty) {
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyDeviceName.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/emptyDeviceName.xml"), false);
    // readXML returns false if the device name is empty
}

/**
 * Test to see if the check for emissions works correctly
 */

TEST_F(InputTests, EmissionsAreNegative) {
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeEmission.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/negativeEmission.xml"), false);
    // readXML returns false if the emissions value is negative
}

/**
 * Test to see if the check for device input works correctly
 */

TEST_F(InputTests, ValidDeviceInput) {
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/validDevice.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/validDevice.xml"), true);
    // readXML returns true if the XML input for the device is valid
}

/**
 * Test to see if the check for type works correctly and is not empty
 */

TEST_F(InputTests, TypeIsEmpty) {
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyType.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/emptyType.xml"), false);
    // readXML returns false type is empty
}



/**
 * Test to see if the check for jobnumbers works correctly
 */

TEST_F(InputTests, jobNrIsNegative){
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeJobnr.xml"));

    System::PrinterSystem testSystem;

    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/negativeJobnr.xml"), false);
    // readXML returns false if the xml is invalid
}

/**
 * Test to see if the check for Jobnumber works correctly and the Jobnumbers are unique
 */

TEST_F(InputTests, Jobnr_unique){
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/notuniqueJobnr.xml"));

    System::PrinterSystem testSystem;

    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/notuniqueJobnr.xml"), false);

}


/**
 * Test to see if the check for Username works correctly and is not empty
 */

TEST_F(InputTests, emptyUserName){
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyUser.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/emptyUser.xml"), false);

}

/**
 * Test to see if the check for page count works correctly
 */

TEST_F(InputTests, pageCountisnegative){
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativePagecount.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/negativePagecount.xml"), false);
    // readXML returns false if the xml is invalid
}



