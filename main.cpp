#include <iostream>
#include "Printer.h"

int main() {



    Printer::PrinterSystem testSystem;

    testSystem.readXML("test.xml");

    testSystem.getInfo("test.txt");





    testSystem.doPrintJob(2189);

    return 0;
}
