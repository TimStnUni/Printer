//
// Created by stand on 19/06/2024.
//

#include "Logger.h"

namespace System {
    Logger::Logger() {

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

    void
    Logger::dispPrintJob(std::ostream &outStream, unsigned int jobNr, std::basic_string<char> deviceName,
                         std::basic_string<char> username,
                         std::basic_string<char> &type, unsigned int pages, float emissions) {


        outStream << "Printer \"" << deviceName << "\" finished " << type << "job:\n";
        outStream << "  Number: " << jobNr << "\n";
        outStream << "  Submitted by \"" << username << "\"\n";
        outStream << "  " << pages << " pages\n";
        outStream << "  Job CO2 emissions: " << emissions << " gram\n";
        outStream << std::endl;
    }

    void Logger::pageAmount(std::ostream &outStream) {

        outStream << "fewer pages remaining, will print all remaining pages" << std::endl;

    }

    void Logger::printConsistency(std::ostream &outStream) {

        outStream << "xmlFile was not consistent" << std::endl;

    }

    void Logger::printNoDevice(std::ostream &outStream, unsigned int jobNr) {

        outStream << "No suitable device found for job " << jobNr << std::endl;

    }

    void Logger::parseNameEmpty(std::ostream & outStream, const std::string& type){

        outStream << type << " should not be empty" << std::endl;

    }

    void Logger::parseNegative(std::ostream & outStream, const std::string& type){

        outStream << type << " should be positive" << std::endl;

    }



} // System