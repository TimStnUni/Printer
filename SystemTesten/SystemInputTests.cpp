//
// Created by tim on 29/02/24.
//
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../Printer.h"


using namespace std;

using namespace System;

class SystemInputTests: public ::testing:: Test{
protected:
    friend class Printer;
    friend class PrinterSystem;

    PrinterSystem testSystem;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};




TEST_F(SystemInputTests, ValidXMLTest){

    EXPECT_EQ(testSystem.readXML("SystemTesten/test.xml"), true);
}

TEST_F(SystemInputTests, SystemDomainTests){

    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/emptyUser.xml"), false);
    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/negativeJobnr.xml"), false);
    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/NegativePagecount.xml"), false);
    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/notuniqueJobnr.xml"), false);
    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/emptyDeviceName.xml"), false);
    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/negativeEmission.xml"), false);
    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/negativeSpeed.xml"), false);

}














