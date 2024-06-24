//
// Created by alyja on 14/03/2024.
//


#include <gtest/gtest.h>

using namespace std;

#include "./Alletesten/allinputtests.cpp"


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}