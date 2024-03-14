//
// Created by alyja on 14/03/2024.
//

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

