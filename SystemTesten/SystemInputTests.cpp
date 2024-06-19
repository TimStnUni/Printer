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

    //Todo: split these into different functions

    /*
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/emptyUser.xml"));
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/negativeJobnr.xml"));
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/negativePagecount.xml"));
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/notuniqueJobnr.xml"));
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/emptyDeviceName.xml"));
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/negativeEmission.xml"));
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/negativeSpeed.xml"));


    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/emptyUser.xml"), false);
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/emptyUser.xml.txt"));
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/emptyUser.xmltest.txt"));
    EXPECT_TRUE(FileCompare("SystemTesten/SystemInputs/emptyUser.xml.txt", "SystemTesten/SystemInputs/emptyUser.xmltest.txt"));


    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/negativeJobnr.xml"), false);
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/negativeJobnr.xml.txt"));
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/negativeJobnr.xmltest.txt"));
    EXPECT_TRUE(FileCompare("SystemTesten/SystemInputs/negativeJobnr.xml.txt", "SystemTesten/SystemInputs/negativeJobnr.xmltest.txt"));

    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/negativePagecount.xml"), false);
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/negativePagecount.xml.txt"));
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/negativePagecount.xmltest.txt"));
    EXPECT_TRUE(FileCompare("SystemTesten/SystemInputs/negativePagecount.xml.txt", "SystemTesten/SystemInputs/negativePagecount.xmltest.txt"));

    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/notuniqueJobnr.xml"), false);
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/notuniqueJobnr.xml.txt"));
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/notuniqueJobnr.xmltest.txt"));
    EXPECT_TRUE(FileCompare("SystemTesten/SystemInputs/notuniqueJobnr.xml.txt", "SystemTesten/SystemInputs/notuniqueJobnr.xmltest.txt"));

    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/emptyDeviceName.xml"), false);
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/emptyDeviceName.xml.txt"));
//    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/emptyDeviceName.xml.txt"));
//    EXPECT_TRUE(FileCompare("SystemTesten/SystemInputs/emptyDeviceName.xmltest.txt", "SystemTesten/SystemInputs/emptyDeviceName.xml.txt"));

    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/negativeEmission.xml"), false);
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/negativeEmission.xml.txt"));
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/negativeEmission.xmltest.txt"));
    EXPECT_TRUE(FileCompare("SystemTesten/SystemInputs/negativeEmission.xml.txt", "SystemTesten/SystemInputs/negativeEmission.xmltest.txt"));

    EXPECT_EQ(testSystem.readXML("SystemTesten/SystemInputs/negativeSpeed.xml"), false);
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/negativeSpeed.xml.txt"));
    EXPECT_TRUE(FileExists("SystemTesten/SystemInputs/negativeSpeed.xmltest.txt"));
    EXPECT_TRUE(FileCompare("SystemTesten/SystemInputs/negativeSpeed.xml.txt", "SystemTesten/SystemInputs/negativeSpeed.xmltest.txt"));


    */
}














