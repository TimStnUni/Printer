//============================================================================
// Name        : JobInputTests.cpp
// Author      : Tim Standaert, Jasmine Castillo, Thomas D'Archambeau
// Date        : 14/03/2024
// Version     : 17++
// Description : PrinterSystem in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;

#include "../Printer.h"
#include "../TicTacToeUtils.h"

class JobInputTests: public ::testing:: Test{
protected:
    friend class Printer;
    friend class Job;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

/**
Tests for Jobnr, Pagecount from Jobs
 */
TEST_F(JobInputTests, jobNrIsNegative){
    ASSERT_TRUE(DirectoryExists("JobTesten/JtestInput"));
    ASSERT_TRUE(FileExists("JobTesten/JtestInput/negativeJobnr.xml"));

    System::PrinterSystem testSystem;
//    ofstream outFile; //create an output file stream
//    string outFileName = "JobTesten/JtestOutput/negativeJobnr.txt";
//    const char *outFileNameChar = outFileName.c_str(); // open the file
//    outFile.open(outFileNameChar);
//    bool readAndPrint = testSystem.readXML("JobTesten/JtestOutput/negativeJobnr.txt", outFile);
//
//    ASSERT_TRUE(DirectoryExists("Tests/JtestOutput"));
//    ASSERT_TRUE(FileExists("JobTesten/JtestOutput/negativeJobnr.txt"));

    EXPECT_EQ(testSystem.readXML("JobTesten/JtestInput/negativeJobnr.xml"), false);
    // readXML returns false if the xml is invalid
}

TEST_F(JobInputTests, Jobnr_unique){
    ASSERT_TRUE(DirectoryExists("JobTesten/JtestInput"));
    ASSERT_TRUE(FileExists("JobTesten/JtestInput/notuniqueJobnr.xml"));

    System::PrinterSystem testSystem;

    EXPECT_EQ(testSystem.readXML("JobTesten/JtestInput/notuniqueJobnr.xml"), false);

}


TEST_F(JobInputTests, emptyUserName){
    ASSERT_TRUE(DirectoryExists("JobTesten/JtestInput"));
    ASSERT_TRUE(FileExists("JobTesten/JtestInput/emptyUser.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("JobTesten/JtestInput/emptyUser.xml"), false);

}

TEST_F(JobInputTests, pageCountisnegative){
    ASSERT_TRUE(DirectoryExists("JobTesten/JtestInput"));
    ASSERT_TRUE(FileExists("JobTesten/JtestInput/negativePagecount.xml"));

    System::PrinterSystem testSystem;
    EXPECT_EQ(testSystem.readXML("JobTesten/JtestInput/negativePagecount.xml"), false);
    // readXML returns false if the xml is invalid
}


