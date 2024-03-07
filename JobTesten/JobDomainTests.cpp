//
// Created by alyja on 14/03/2024.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;

#include "../Printer.h"

class JobDomainTests: public ::testing::Test {
protected:
    friend class Job;

};

/**
Tests the default constructor.
*/