//
// Created by stand on 28/04/2024.
//

#ifndef PROJSOFTENG_INFOPRINTER_H
#define PROJSOFTENG_INFOPRINTER_H

#include "Device.h"
#include "Job.h"

#include <fstream>


namespace System {
    class PrinterSystem;


    class InfoPrinter {


    public:
        InfoPrinter();
        void setSystem(PrinterSystem * inSystem);
        void printAscii(std::ostream &writestream);



    protected:

        std::ofstream outStream;

        PrinterSystem * ownSystem;
        InfoPrinter * _initcheck;


        bool properlyInitialized();

    };

}
#endif //PROJSOFTENG_INFOPRINTER_H
