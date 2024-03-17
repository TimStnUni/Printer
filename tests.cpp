//============================================================================
// Name        : tests.cpp
// Author      : Tim Standaert, Jasmine Castillo, Thomas D'Archambeau
// Date        : 29/02/2024
// Version     : 17++
// Description : PrinterSystem in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;
#include "Printer.h"
#include "./PrinterTesten/PrinterDomainTests.cpp"
#include "./PrinterTesten/PrinterOutputTests.cpp"
#include "./PrinterTesten/PrinterInputTests.cpp"
#include "./JobTesten/JobInputTests.cpp"
#include "./JobTesten/JobOutputTests.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

