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

        void printError(std::ostream & outStream, std::string message);

        void printerAssignmentError(std::ostream & outStream, unsigned int jobNr);


    private:

        bool properlyInitialized();

        Logger * _initCheck;


    };

} // System

#endif //PROJSOFTENG_LOGGER_H
