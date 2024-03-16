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

//    char cwd[1024];
//    if (getcwd(cwd, sizeof(cwd)) != NULL) {
//        std::cout << "Current working directory: " << cwd << std::endl;
//    } else {
//        std::cerr << "getcwd() error" << std::endl;
//        return 1;
//    }
//    return 0;
    System::PrinterSystem testSystem;


    testSystem.readXML("test.xml");

    testSystem.getInfo("test.txt");

    testSystem.doPrintJob(89751);
    testSystem.printAll();


    return 0;
}
