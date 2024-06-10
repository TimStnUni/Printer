//
// Created by tim on 29/02/24.
//
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../Printer.h"


using namespace std;

using namespace System;

class XMLTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    // Declares the variables your tests want to use.
    XMLParser ppp_;
};



TEST_F(XMLTest, AfterParse){

    //Todo: Should add a test for type

    ppp_.addInputFile("PrinterTesten/PrinterTestenInputs/test.xml");
    EXPECT_EQ(ppp_.getJobList().size(), 2);
    EXPECT_EQ(ppp_.getJobList().begin()->getJobNr(), 89751);
    //This should read in a valid file, with 2 jobs, and first job should be 89751
    EXPECT_EQ(ppp_.getDeviceList().size(), 1);
    EXPECT_EQ(ppp_.getDeviceList().at(0).getNameDev(), "Office_Printer5");
    EXPECT_EQ(ppp_.getDeviceList().at(0).getEmissions(), 3);
    EXPECT_EQ(ppp_.getDeviceList().at(0).getSpeed(), 40);
    //This should read in a valid file, with 1 device, and the correct name, emissions and speed


}

TEST_F(XMLTest, DomainInvalids_negEms){

    EXPECT_EQ(ppp_.addInputFile("Alletesten/testinput/negativeEmission.xml"), false);
    EXPECT_EQ(ppp_.addInputFile("Alletesten/testinput/negativeSpeed.xml"), false);
    EXPECT_EQ(ppp_.addInputFile("Alletesten/testinput/emptyDeviceName.xml"), false);


}


TEST_F(XMLTest, ValidTest){
    EXPECT_EQ(ppp_.addInputFile("Alletesten/testinput/validDevice.xml"), true);
}








