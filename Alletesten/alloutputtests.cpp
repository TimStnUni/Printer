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


using namespace std;

using namespace System;
class OutputTests: public ::testing:: Test {
protected:
    friend class Printer;
    friend class Device;
    friend class Job;
    friend class PrinterSystem;

    PrinterSystem testSystem;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};


TEST_F(OutputTests, SingleJobTest){


    testSystem.readXML("SystemTesten/test.xml");

    std::ofstream outFile; // Create an output file stream
    std::string f = "SystemTesten/PrintOutput";
    std::string outputFileName = f + ".txt";
    const char *outputFileNameChar = outputFileName.c_str();
    outFile.open(outputFileNameChar); // Open the file


    testSystem.doPrintJob(2189, outFile);

    outFile.close();

    EXPECT_TRUE(FileExists("SystemTesten/PrintOutputTest.txt"));
    EXPECT_TRUE(FileExists("SystemTesten/PrintOutput.txt"));
    EXPECT_TRUE(FileCompare("SystemTesten/PrintOutputTest.txt", "SystemTesten/PrintOutput.txt"));
    EXPECT_TRUE(FileCompare("SystemTesten/PrintOutput.txt", "SystemTesten/PrintOutputTest.txt"));


}


TEST_F(OutputTests, AllJobTest){


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