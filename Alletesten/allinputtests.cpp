//
// Created by alyja on 14/03/2024.
//
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;

#include "../Printer.h"
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
 *  inputTests for Device
 */

TEST_F(InputTests, DeviceNameIsEmpty) {
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyDeviceName.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/emptyDeviceName.xml"), false);
    // readXML returns false if the device name is empty
}

TEST_F(InputTests, EmissionsAreNegative) {
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeEmission.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/negativeEmission.xml"), false);
    // readXML returns false if the emissions value is negative
}



TEST_F(InputTests, ValidDeviceInput) {
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/validDevice.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/validDevice.xml"), true);
    // readXML returns true if the XML input for the device is valid
}

TEST_F(InputTests, SpeedIsNegativeDeathTest) {
    System::Device dev;
    int speed = -1;
    EXPECT_DEATH(dev.setSpeed(speed), "Speed should be positive");
}

TEST_F(InputTests, EmissionsAreNegativeDeathTest) {
    System::Device dev;
    int emissions = -1;
    EXPECT_DEATH(dev.setEmissions(emissions), "Emissions should be positive");
}


/**
 * inputTests for Job
 */

TEST_F(InputTests, jobNrIsNegative){
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeJobnr.xml"));

    System::PrinterSystem testSystem;

    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/negativeJobnr.xml"), false);
    // readXML returns false if the xml is invalid
}

TEST_F(InputTests, Jobnr_unique){
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/notuniqueJobnr.xml"));

    System::PrinterSystem testSystem;

    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/notuniqueJobnr.xml"), false);

}


TEST_F(InputTests, emptyUserName){
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyUser.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/emptyUser.xml"), false);

}

TEST_F(InputTests, pageCountisnegative){
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativePagecount.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/negativePagecount.xml"), false);
    // readXML returns false if the xml is invalid
}

TEST_F(InputTests, NegativeDeathTests){
    System::Job job;

    EXPECT_DEATH(job.setUserName(""), "Username should not be empty");
    EXPECT_DEATH(job.setPageCount(-5), "Pagecount should be positive");
    EXPECT_DEATH(job.setJobNr(-5), "jobnr should be positive");

}

