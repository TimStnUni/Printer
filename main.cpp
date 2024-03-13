#include <iostream>
#include "Printer.h"

int main() {



    Printer::PrinterSystem testSystem;

    testSystem.readXML("test.xml");

    testSystem.getInfo("test.txt");




    //Todo: This causes a segfault. i thought i knew why but i have lost this knowledge
    //testSystem.doPrintJob(89751);

    return 0;
}
