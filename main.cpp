//============================================================================
// Name        : main.cpp
// Author      : Tim Standaert, modified by Jasmine Castillo
// Version     :
// Description :
//============================================================================

#include <unistd.h>
#include <iostream>
#include "Printer.h"

int main() {


    System::PrinterSystem testSystem;


    bool consistent = testSystem.readXML("DeviceTesten/DevtestInput/invalidDevice.xml");


    std::ofstream outFile; // Create an output file stream
    std::string f = "PrintOutputTest";
    std::string outputFileName = f + ".txt";
    const char *outputFileNameChar = outputFileName.c_str();
    outFile.open(outputFileNameChar); // Open the file



    if(consistent){
        //testSystem.getInfo("test.txt");
        //testSystem.doPrintJob(89751, outFile);
        //testSystem.printAll(outFile);

    }

    outFile.close();
    return 0;
}
