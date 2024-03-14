//
// Created by tim on 29/02/24.
//

#include "gtest/gtest.h"
#include "Printer.h"
#include "JobTesten/JobInputTests.cpp"


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


//TEST_F(XMLTest, AfterParse){
//    XMLParser testParser("test.xml");
//
//    EXPECT_EQ(testParser.getJobList().size(), 2);
//    EXPECT_EQ(testParser.getJobList().begin()->getJobNr(), 89751);
//
//
//}


int main(int argc, char ** argv){

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();





    return 0;
}



