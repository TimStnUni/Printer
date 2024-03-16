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
    ASSERT_TRUE(FileExists("JobTesten/JtestInput/negativeJobnr1.xml"));

    System::PrinterSystem testSystem;

    EXPECT_EQ(testSystem.readXML("JobTesten/JtestInput/negativeJobnr1.xml"), false);
    // readXML returns false if the xml is invalid

}

TEST_F(JobInputTests, Jobnr_unique){
    ASSERT_TRUE(DirectoryExists("JobTesten/JtestInput"));
    ASSERT_TRUE(FileExists("JobTesten/JtestInput/notuniqueJobnr.xml"));
}



