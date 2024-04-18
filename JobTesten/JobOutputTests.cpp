//============================================================================
// Name        : JobOutputTests.cpp
// Author      : Tim Standaert, Jasmine Castillo, Thomas D'Archambeau
// Date        : 14/03/2024
// Version     : 17++
// Description : PrinterSystem in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;

#include "../TicTacToeUtils.h"
#include "../Printer.h"

class JobOutputTests: public ::testing:: Test {
protected:
    friend class Job;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};


//test

