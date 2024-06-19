//
// Created by stand on 19/06/2024.
//

#include "Logger.h"

namespace System {
    Logger::Logger(){

        _initCheck = this;

        ENSURE(properlyInitialized(), "logger was not properly initialized");


    }



    bool Logger::properlyInitialized() {
        return this == _initCheck;
    }

    void Logger::printError(std::ostream &outStream, std::string message) {

        REQUIRE(!message.empty(), "Message should not be empty");

        outStream << message << std::endl;

    }

    void Logger::printerAssignmentError(std::ostream &outStream, unsigned int jobNr) {

        outStream << "job " << jobNr << " was not assigned to this printer." << std::endl;

    }


} // System