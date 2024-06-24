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
    friend class Scheduler;

    PrinterSystem testSystem;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

/**
 * Tests if the doPrintJob works correctly and has the right output
 */

TEST_F(OutputTests, SingleJobTest){


    testSystem.readXML("Alletesten/testoutput/outputtest.xml");

    std::ofstream outFile; // Create an output file stream
    std::string f = "Alletesten/testoutput/PrintOutput";
    std::string outputFileName = f + ".txt";
    const char *outputFileNameChar = outputFileName.c_str();
    outFile.open(outputFileNameChar); // Open the file


    testSystem.doPrintJob("Color_Printer", outFile);

    outFile.close();

    EXPECT_TRUE(FileExists("Alletesten/testoutput/PrintOutputTest.txt"));
    EXPECT_TRUE(FileExists("Alletesten/testoutput/PrintOutput.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testoutput/PrintOutputTest.txt", "Alletesten/testoutput/PrintOutput.txt"));

}

/**
 * Tests if the function printFull works correctly and has the right output
 */

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

/**
 * Tests if the function
 */


TEST_F(OutputTests, ScheduledJobTest){

    testSystem.readXML("Alletesten/testoutput/outputtest.xml");

    std::ofstream outFile; // Create an output file stream
    std::string f = "Alletesten/testoutput/ScheduleJobOutput";
    std::string outputFileName = f + ".txt";
    const char *outputFileNameChar = outputFileName.c_str();
    outFile.open(outputFileNameChar); // Open the file


    testSystem.doPrintJob("Color_Printer", outFile);

    outFile.close();

    EXPECT_TRUE(FileExists("Alletesten/testoutput/ScheduleJobOutput.txt"));
    EXPECT_TRUE(FileExists("Alletesten/testoutput/ScheduleJobOutputTest.txt"));
    EXPECT_TRUE(FileCompare("Alletesten/testoutput/ScheduleJobOutput.txt", "Alletesten/testoutput/ScheduleJobOutputTest.txt"));


}



TEST_F(OutputTests, InfoSysText){

    ASSERT_TRUE(DirectoryExists("Alletesten/testoutput"));
    ASSERT_TRUE(FileExists("Alletesten/testoutput/outputtest.xml"));

    System::PrinterSystem testSystem;

    EXPECT_EQ(testSystem.readXML("Alletesten/testoutput/outputtest.xml"), true);

    std::ofstream outFile; // Create an output file stream
    std::string f = "Alletesten/testoutput/AsciiSysText.xml";
    std::string outputFileName = f + ".txt";
    const char *outputFileNameChar = outputFileName.c_str();
    outFile.open(outputFileNameChar); // Open the file

    testSystem.getInfo(outFile, "ASCII", true);
    outFile.close();


    ASSERT_TRUE(FileExists("Alletesten/testoutput/AsciiSysText.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testoutput/AsciiSysText.txt"));

    EXPECT_TRUE(FileCompare("Alletesten/testoutput/AsciiSysText.xml.txt",
                            "Alletesten/testoutput/AsciiSysText.txt"));

}


/*
TEST_F(OutputTests, InfoSystemgraph){

    ASSERT_TRUE(DirectoryExists("Alletesten/testoutput"));
    ASSERT_TRUE(FileExists("Alletesten/testoutput/outputtest.xml"));

    System::PrinterSystem testSystem;

    EXPECT_EQ(testSystem.readXML("Alletesten/testoutput/outputtest.xml"), true);

    std::ofstream outFile; // Create an output file stream
    std::string f = "Alletesten/testoutput/ASCIISysGraph.xml";
    std::string outputFileName = f + ".txt";
    const char *outputFileNameChar = outputFileName.c_str();
    outFile.open(outputFileNameChar); // Open the file
//TODO:
//    testSystem.getSystemGraph(outFile, "ASCII");
    outFile.close();


    ASSERT_TRUE(FileExists("Alletesten/testoutput/ASCIISysGraph.xml.txt"));
    ASSERT_TRUE(FileExists("Alletesten/testoutput/ASCIISysGraph.txt"));

    EXPECT_TRUE(FileCompare("Alletesten/testoutput/ASCIISysGraph.xml.txt",
                            "Alletesten/testoutput/ASCIISysGraph.txt"));

}
 */