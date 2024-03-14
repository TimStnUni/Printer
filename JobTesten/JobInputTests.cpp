//
// Created by alyja on 14/03/2024.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;

#include "../Printer.h"
#include "TicTacToeUtils.h"

class JobInputTests: public ::testing:: Test{
protected:
    friend class Job;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(JobInputTests, checkneg_jobnr){
    ASSERT_TRUE(DirectoryExists("JtestInput"));
    ASSERT_TRUE(FileExists("JtestInput/negativeJobnr.xml"));




}