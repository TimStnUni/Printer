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


    testSystem.readXML("Alletesten/testoutput/outputtest.xml");

    std::ofstream outFile; // Create an output file stream
    std::string f = "Alletesten/testoutput/PrintOutput";
    std::string outputFileName = f + ".txt";
    const char *outputFileNameChar = outputFileName.c_str();
    outFile.open(outputFileNameChar); // Open the file


    testSystem.doPrintJob(2189, outFile);

    outFile.close();

    EXPECT_TRUE(FileExists("Alletesten/testoutput/PrintOutputTest.txt"));
    EXPECT_TRUE(FileExists("Alletesten/testoutput/PrintOutput.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testoutput/PrintOutputTest.txt", "Alletesten/testoutput/PrintOutput.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testoutput/PrintOutput.txt", "Alletesten/testoutput/PrintOutputTest.txt"));

}


TEST_F(OutputTests, AllJobTest){

    testSystem.readXML("Alletesten/testoutput/outputtest.xml");

    std::ofstream outFile; // Create an output file stream
    std::string f = "Alletesten/testoutput/PrintAllOutput";
    std::string outputFileName = f + ".txt";
    const char *outputFileNameChar = outputFileName.c_str();
    outFile.open(outputFileNameChar); // Open the file


    testSystem.printAll(outFile);

    outFile.close();

    EXPECT_TRUE(FileExists("Alletesten/testoutput/PrintAllOutput.txt"));
    EXPECT_TRUE(FileExists("Alletesten/testoutput/PrintAllOutputTest.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testoutput/PrintAllOutput.txt", "Alletesten/testoutput/PrintAllOutputTest.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testoutput/PrintAllOutputTest.txt", "Alletesten/testoutput/PrintAllOutput.txt"));


}