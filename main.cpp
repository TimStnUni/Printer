//============================================================================
// Name        : main.cpp
// Author      : Tim Standaert, Jasmine Castillo, Thomas D'Archambeau
// Date        : 29/02/2024
// Version     : 17++
// Description : PrinterSystem in C++, Ansi-style
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

    testSystem.getInfo("testje.txt");

    bool consistent = testSystem.readXML("test.xml");

    if(consistent){
        testSystem.getInfo("test.txt");
        testSystem.doPrintJob(89751);
        testSystem.printAll();

    }

    return 0;
}
