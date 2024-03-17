//
// Created by tim on 29/02/24.
//
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

using namespace std;

#include "../Printer.h"
#include "../TicTacToeUtils.h"

class DeviceInputTests: public ::testing:: Test{
protected:
    friend class Printer;
    friend class Device;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};








