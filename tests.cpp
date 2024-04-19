//
// Created by alyja on 14/03/2024.
//


#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;
#include "Printer.h"
#include "./PrinterTesten/PrinterDomainTests.cpp"
#include "./PrinterTesten/PrinterOutputTests.cpp"
#include "./PrinterTesten/PrinterInputTests.cpp"
//#include "./JobTesten/JobInputTests.cpp"
//#include "./JobTesten/JobOutputTests.cpp"
//#include "./DeviceTesten/DeviceInputTests.cpp"
#include "./Alletesten/alltests.cpp"
#include "./SystemTesten/SystemInputTests.cpp"
#include "./SystemTesten/SystemOutputTests.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}