#include <iostream>
#include "Printer.h"

int main() {

    XMLParser test("test.xml");

    Printer::PrinterSystem testSystem;

    testSystem.readXML("test.xml");

    testSystem.getInfo("test.txt");


    return 0;
}
