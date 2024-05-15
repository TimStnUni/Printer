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
using namespace std;

using namespace System;

class InputTests: public ::testing::Test {
protected:
    friend class Printer;
    friend class Device;
    friend class Job;
    friend class Printer;
    friend class PrinterSystem;
    PrinterSystem testSystem;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};


TEST_F(InputTests, ValidXMLTests){
    EXPECT_EQ(testSystem.readXML("SystemTesten/test.xml"), true);
}

TEST_F(InputTests, InputTesten){
    /**
     * readXML returns false if the device name is empty and the output is not the same as the created .txt file
    */
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyDeviceName.xml"));
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/emptyDeviceName.xml"), false);

    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyDeviceName.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyDeviceName.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testinput/emptyDeviceName.xml.txt",
                            "Alletesten/testinput/emptyDeviceName.txt"));


    /**
     * Test to see if the check for emissions works correctly
     * readXML returns false if the emissions value is negative and the output is not the same as the created .txt file
     */
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeEmission.xml"));
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/negativeEmission.xml"), false);

    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeEmission.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeEmission.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testinput/negativeEmission.xml.txt",
                            "Alletesten/testinput/negativeEmission.txt"));


    /**
     * Test to see if the check for device input works correctly
     * readXML returns true if the XML input for the device is valid
     * and the output is not the same as the created .txt file
     */
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/validDevice.xml"));
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/validDevice.xml"), true);

    ASSERT_TRUE(FileExists("Alletesten/testinput/validDevice.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/validDevice.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testinput/validDevice.xml.txt",
                            "Alletesten/testinput/validDevice.txt"));


    /**
     * Test to see if the check for type works correctly and is not empty
     * readXML returns false type is empty and the output is not the same as the created .txt file
     */

    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyType.xml"));
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/emptyType.xml"), false);

    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyType.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyType.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testinput/emptyType.xml.txt",
                            "Alletesten/testinput/emptyType.txt"));


    /**
     * Test to see if the check for jobnumbers works correctly
     * readXML returns false if the xml is invalid and the output is not the same as the created .txt file
     */
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeJobnr.xml"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeJobnr.txt"));
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/negativeJobnr.xml"), false);

    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeJobnr.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativeJobnr.xml.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testinput/negativeJobnr.xml.txt",
                            "Alletesten/testinput/negativeJobnr.txt"));


    /**
     * Test to see if the check for Jobnumber works correctly and the Jobnumbers are unique
     *  readXML returns false if the Jobnr is not unique and the output is not the same as the created .txt file
     */
    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/notuniqueJobnr.xml"));
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/notuniqueJobnr.xml"), false);

    ASSERT_TRUE(FileExists("Alletesten/testinput/notuniqueJobnr.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/notuniqueJobnr.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testinput/notuniqueJobnr.xml.txt",
                            "Alletesten/testinput/notuniqueJobnr.txt"));


    /**
     * Test to see if the check for Username works correctly and is not empty
     * readXML returns false if the Username is empty and the output is not the same as the created .txt file
     */

    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyUser.xml"));
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/emptyUser.xml"), false);

    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyUser.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/emptyUser.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testinput/emptyUser.xml.txt",
                            "Alletesten/testinput/emptyUser.txt"));



    /**
     * Test to see if the check for page count works correctly
     * readXML returns false if the pagecount is negative and the output is not the same as the created .txt file
     */

    ASSERT_TRUE(DirectoryExists("Alletesten/testinput"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativePagecount.xml"));
    EXPECT_EQ(testSystem.readXML("Alletesten/testinput/negativePagecount.xml"), false);

    ASSERT_TRUE(FileExists("Alletesten/testinput/negativePagecount.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testinput/negativePagecount.xml.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testinput/negativePagecount.xml.txt",
                            "Alletesten/testinput/negativePagecount.txt"));

    
}




