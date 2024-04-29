//============================================================================
// Name        : main.cpp
// Author      : Tim Standaert, modified by Jasmine Castillo
// Version     :
// Description :
//============================================================================

#include <unistd.h>
#include <iostream>
#include "PrinterSystem.h"

int main() {


    System::PrinterSystem testSystem;

    //UseCase 1: Reads an XML file into the printersystem
    bool consistent = testSystem.readXML("test.xml");
    //System::PrinterSystem testSystem2 = testSystem;

    //testSystem.getInfo("Usecase2Info.txt");


    std::ofstream outFile; // Create an output file stream
    std::string f = "PrintOutputTestScheduled";
    std::string outputFileName = f + ".txt";
    const char *outputFileNameChar = outputFileName.c_str();
    outFile.open(outputFileNameChar); // Open the file


    std::ofstream outFile2; // Create an output file stream
    std::string f2 = "PrintAllOutputTest";
    std::string outputFileName2 = f2 + ".txt";
    const char *outputFileNameChar2 = outputFileName2.c_str();
    outFile2.open(outputFileNameChar2); // Open the file





    if(consistent){
        //Usecase 2: Basic info about the printer system
        //testSystem.getInfo(std::cout, "ASCII");

        //Usecase 3.1: manual processing
        //testSystem.doPrintJob(2189, outFile);
        //testSystem.printAll(outFile2);
        //Usecase 3.2: automatic processing
        testSystem.printAll(std::cout);

    }

//    outFile.close();
//    outFile2.close();
    return 0;
}
