#include <iostream>
#include "Printer.h"

int main() {

    Printer::XMLParser test("test.xml");


    Printer::Device testDevice(test.getName(), test.getEmissions(), test.getSpeed());



    std::unordered_set<int> testset;
    testset.insert(5);
    testset.insert(5);

    Printer::PrinterSystem System;

    System.readXML("test.xml");

    return 0;
}
