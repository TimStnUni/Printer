//
// Created by alyja on 24/04/2024.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;


#include "../PrinterSystem.h"
#include "../TicTacToeUtils.h"

class DomainTests: public ::testing::Test {
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
 * domainTests for Device
 */

TEST_F(DomainTests, SpeedIsNegativeDeathTest) {
    System::Device dev;
    int speed = -1;
    EXPECT_DEATH(dev.setSpeed(speed), "Speed should be positive");
}

TEST_F(DomainTests, EmissionsAreNegativeDeathTest) {
    System::Device dev;
    int emissions = -1;
    EXPECT_DEATH(dev.setEmissions(emissions), "Emissions should be positive");
}


/**
 * domainTests for Job
 */

TEST_F(DomainTests, NegativeDeathTests){
    System::Job job;

    EXPECT_DEATH(job.setPageCount(-5), "Pagecount should be positive");
    EXPECT_DEATH(job.setJobNr(-5), "jobnr should be positive");
    EXPECT_DEATH(job.setPageCount(-24), "Pagecount should be positive");
    EXPECT_DEATH(job.setJobNr(-5), "jobnr should be positive");
}

TEST_F(DomainTests, EmptyJobNameTests){
    System::Job job;

    EXPECT_DEATH(job.setUserName(""), "Username should not be empty");
}

TEST_F(DomainTests, EmptyTypeTests){
    System::Job job;

    EXPECT_DEATH(job.setType(""), "Type should not be empty");
}

