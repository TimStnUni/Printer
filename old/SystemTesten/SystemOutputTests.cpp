//
// Created by alyja on 14/03/2024.
//
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "../Printer.h"
#include "../../TicTacToeUtils.h"


using namespace std;

using namespace System;
class SystemOutputTests: public ::testing:: Test{
protected:
    friend class Printer;
    friend class PrinterSystem;

    PrinterSystem testSystem;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};


TEST_F(SystemOutputTests, SingleJobTest){
/*

    testSystem.readXML("SystemTesten/test.xml");

    std::ofstream outFile; // Create an output file stream
    std::string f = "SystemTesten/PrintOutput";
    std::string outputFileName = f + ".txt";
    const char *outputFileNameChar = outputFileName.c_str();
    outFile.open(outputFileNameChar); // Open the file


    testSystem.doPrintJob("Office_Printer5", outFile);

    outFile.close();

    EXPECT_TRUE(FileExists("SystemTesten/PrintOutputTest.txt"));
    EXPECT_TRUE(FileExists("SystemTesten/PrintOutput.txt"));
    EXPECT_TRUE(FileCompare("SystemTesten/PrintOutputTest.txt", "SystemTesten/PrintOutput.txt"));

*/
}


TEST_F(SystemOutputTests, AllJobTest){

    ASSERT_TRUE(FileExists("SystemTesten/test.xml"));
    testSystem.readXML("SystemTesten/test.xml");



    std::ofstream outFile; // Create an output file stream
    std::string f = "SystemTesten/PrintAllOutput";
    std::string outputFileName = f + ".txt";
    const char *outputFileNameChar = outputFileName.c_str();
    outFile.open(outputFileNameChar); // Open the file





    testSystem.printAll(outFile);

    outFile.close();

    EXPECT_TRUE(FileExists("SystemTesten/PrintAllOutput.txt"));
    EXPECT_TRUE(FileExists("SystemTesten/PrintAllOutputTest.txt"));
    EXPECT_TRUE(FileCompare("SystemTesten/PrintAllOutput.txt", "SystemTesten/PrintAllOutputTest.txt"));
    EXPECT_TRUE(FileCompare("SystemTesten/PrintAllOutputTest.txt", "SystemTesten/PrintAllOutput.txt"));


}