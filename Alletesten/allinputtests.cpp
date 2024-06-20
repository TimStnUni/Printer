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
    testSystem.readXML("Alletesten/testinput/emptyDeviceName.xml");
    //EXPECT_EQ(testSystem.readXML("Alletesten/testinput/emptyDeviceName.xml"), false);
    // readXML returns false if the device name is empty

    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyDeviceName.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyDeviceName.txt"));

    EXPECT_TRUE(FileCompare("Alletesten/testinput/emptyDeviceName.xml.txt",
                            "Alletesten/testinput/emptyDeviceName.txt"));
}

/**
 * Test to see if the check for emissions works correctly
 */

TEST_F(InputTests, EmissionsAreNegative) {
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeEmission.xml"));

    System::PrinterSystem testSystem;
    testSystem.readXML("Alletesten/testinput/negativeEmission.xml");
    //EXPECT_EQ(testSystem.readXML("Alletesten/testinput/negativeEmission.xml"), false);
    // readXML returns false if the emissions value is negative
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeEmission.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeEmission.txt"));

    EXPECT_TRUE(FileCompare("Alletesten/testinput/negativeEmission.xml.txt",
                            "Alletesten/testinput/negativeEmission.txt"));
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

    ASSERT_TRUE(FileExists("Alletesten/testinput/validDevice.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/validDevice.txt"));

    EXPECT_TRUE(FileCompare("Alletesten/testinput/validDevice.xml.txt",
                            "Alletesten/testinput/validDevice.txt"));
}

/**
 * Test to see if the check for type works correctly and is not empty
 */

TEST_F(InputTests, TypeIsEmpty) {
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyType.xml"));

    System::PrinterSystem testSystem;
    testSystem.readXML("Alletesten/testinput/emptyType.xml");
    //EXPECT_EQ(testSystem.readXML("Alletesten/testinput/emptyType.xml"), false);
    // readXML returns false type is empty
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyType.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyType.txt"));

    EXPECT_TRUE(FileCompare("Alletesten/testinput/emptyType.xml.txt",
                            "Alletesten/testinput/emptyType.txt"));
}



/**
 * Test to see if the check for jobnumbers works correctly
 */

TEST_F(InputTests, jobNrIsNegative){
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeJobnr.xml"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeJobnr.txt"));

    System::PrinterSystem testSystem;

    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/negativeJobnr.xml"), false);

    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeJobnr.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeJobnr.xml.txt"));
    // readXML returns false if the xml is invalid
    EXPECT_TRUE(FileCompare("Alletesten/testinput/negativeJobnr.xml.txt",
                            "Alletesten/testinput/negativeJobnr.txt"));
}

/**
 * Test to see if the check for Jobnumber works correctly and the Jobnumbers are unique
 */

TEST_F(InputTests, Jobnr_unique){
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/notuniqueJobnr.xml"));

    System::PrinterSystem testSystem;

    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/notuniqueJobnr.xml"), false);

    ASSERT_TRUE(FileExists("Alletesten/testinput/notuniqueJobnr.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/notuniqueJobnr.txt"));

    EXPECT_TRUE(FileCompare("Alletesten/testinput/notuniqueJobnr.xml.txt",
                            "Alletesten/testinput/notuniqueJobnr.txt"));

}


/**
 * Test to see if the check for Username works correctly and is not empty
 */

TEST_F(InputTests, emptyUserName){
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyUser.xml"));

    System::PrinterSystem testSystem;
    testSystem.readXML("Alletesten/testinput/emptyUser.xml");
    //EXPECT_EQ(testSystem.readXML("Alletesten/testinput/emptyUser.xml"), false);

    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyUser.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyUser.txt"));

    EXPECT_TRUE(FileCompare("Alletesten/testinput/emptyUser.xml.txt",
                            "Alletesten/testinput/emptyUser.txt"));
}

/**
 * Test to see if the check for page count works correctly
 */

TEST_F(InputTests, pageCountisnegative){
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativePagecount.xml"));

    System::PrinterSystem testSystem;

    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/negativePagecount.xml"), false);

    ASSERT_TRUE(FileExists("Alletesten/testinput/negativePagecount.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativePagecount.xml.txt"));

    EXPECT_TRUE(FileCompare("Alletesten/testinput/negativePagecount.xml.txt",
                            "Alletesten/testinput/negativePagecount.txt"));
}


TEST_F(InputTests, InfoPrinter){

    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/infoPrinter.xml"));

    System::PrinterSystem testSystem;

    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/infoPrinter.xml"), true);

    std::ofstream outFile; // Create an output file stream
    std::string f = "Alletesten/testinput/infoPrinter.xml";
    std::string outputFileName = f + ".txt";
    const char *outputFileNameChar = outputFileName.c_str();
    outFile.open(outputFileNameChar); // Open the file

    testSystem.getInfo(outFile, "ASCII");
    outFile.close();


    ASSERT_TRUE(FileExists("Alletesten/testinput/infoPrinter.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/infoPrinter.txt"));

    EXPECT_TRUE(FileCompare("Alletesten/testinput/infoPrinter.xml.txt",
                            "Alletesten/testinput/infoPrinter.txt"));

}


