//
// Created by stand on 19/06/2024.
//

#ifndef PROJSOFTENG_LOGGER_H
#define PROJSOFTENG_LOGGER_H

#include <iostream>
#include <fstream>
#include "DesignByContract.h"

namespace System {

    class Logger {

    public:

        /**
         * \brief constructor for the logger class
         * ENSURE(properlyInitialized(), "logger was not properly initialized");
         */

        Logger();

        void printError(std::ostream &outStream, std::string message);

        void printerAssignmentError(std::ostream &outStream, unsigned int jobNr);

        void dispPrintJob(std::ostream &outStream, unsigned int jobNr, std::basic_string<char> deviceName, std::basic_string<char> username,
                          std::basic_string<char> & type, unsigned int pages, float emissions);

        void pageAmount(std::ostream & outStream);

        void printConsistency(std::ostream & outStream);

        void printNoDevice(std::ostream & outStream, unsigned int jobNr);

        static void parseNameEmpty(std::ostream & outStream, const std::string& type);

        static void parseNegative(std::ostream & outStream, const std::string& type);





    private:

        bool properlyInitialized();

        Logger *_initCheck;


    };

} // System

#endif //PROJSOFTENG_LOGGER_H
