//
// Created by Darch on 17/03/2024.
//
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace std;

#include "../Printer.h"
#include "../TicTacToeUtils.h"

class DeviceInputTests: public ::testing::Test {
protected:
    friend class Device;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};