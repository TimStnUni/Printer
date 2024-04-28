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

        /**
         * \brief Constructor for an InfoPrinter
         * ENSURE(this->properlyInitialized(), "Infoprinter was not properly initialized")
         */
        InfoPrinter();

        /**
         * \brief Setter function for the system for which we are printing
         * @param inSystem
         * REQUIRE(properlyInitialized(), "InfoPrinter not properly initialized when attempting to set system")
         * ENSURE(ownSystem == inSystem, "System was not correclty assigned")
         */

        void setSystem(PrinterSystem * inSystem);

        /**
         * \brief Function that prints info about the system in an ASCII format, and gives it to the writestream
         * @param writestream
         * REQUIRE(properlyInitialized(), "InfoPrinter was not properly initialized when attempting to print ASCII")
         */

        void printAscii(std::ostream &writestream);



    protected:

        std::ofstream outStream;

        PrinterSystem * ownSystem;
        InfoPrinter * _initcheck;


        bool properlyInitialized();

    };

}
#endif //PROJSOFTENG_INFOPRINTER_H
