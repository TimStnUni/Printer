#include <iostream>
#include "XMLParser.h"
#include "Printer.h"

int main() {

    XMLParser test("test.xml");


    Printer::Device testDevice(test.getName(), test.getEmissions(), test.getSpeed());



    Printer::PrinterSystem System;

    System.readXML("test.xml");

    return 0;
}
