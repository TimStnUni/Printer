#include <iostream>
#include "Printer.h"

int main() {



    Printer::PrinterSystem testSystem;



    testSystem.readXML("test.xml");

    testSystem.getInfo("test.txt");



//Tes

    testSystem.doPrintJob(89751);


    testSystem.printAll();

    return 0;
}
