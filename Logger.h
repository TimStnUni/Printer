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

        /**
         * \brief generic error printing function
         * @param outStream stream to print error to
         * @param message message to be printed
         */
        static void printError(std::ostream &outStream, std::string message);

        /**
         * \brief Specific function to indicate a job was not part of a device's queue. Unused currently
         * @param outStream
         * @param jobNr
         */

        static void printerAssignmentError(std::ostream &outStream, unsigned int jobNr);

        /**
         * \brief Function to print the output of a specific job. Has way too many inputs. These are needed to not tell this class what a job/device are Should maybe be moved to infoprinter, since that already knows about jobs
         * @param outStream
         * @param jobNr
         * @param deviceName
         * @param username
         * @param type
         * @param pages
         * @param emissions
         */

        static void dispPrintJob(std::ostream &outStream, unsigned int jobNr, std::basic_string<char> deviceName, std::basic_string<char> username,
                          std::basic_string<char> & type, unsigned int pages, float emissions);


        /**
         * \brief Function to print a remaning pages < printjob(pages) error
         * @param outStream
         */
        static void pageAmount(std::ostream & outStream);

        /**
         * \brief Function to print a consistency error
         * @param outStream
         */

        static void printConsistency(std::ostream & outStream);

        /**
         * \brief Function to print the lack of available device for a job
         * @param outStream
         * @param jobNr
         * REQUIRE(jobNr > 0, "Jobnr should be positive")
         */

        static void printNoDevice(std::ostream & outStream, unsigned int jobNr);

        /**
         * \brief Function to print some parsing error
         * @param outStream
         * @param type
         * REQUIRE(!type.empty(), "Field type should not be empty");
         */
        static void parseNameEmpty(std::ostream & outStream, const std::string& type);

        /**
         * \brief Function to print some parsing error
         * @param outStream
         * @param type
         * REQUIRE(!type.empty(), "Field type should not be empty")
         */

        static void parseNegative(std::ostream & outStream, const std::string& type);

        /**
         * \brief Function to indicate the exceeding limits error
         * @param outStream
         * @param name
         * REQUIRE(!name.empty(), "Name should not be empty");
         */

        static void exceededLimits(std::ostream & outStream, const std::string& name);





    private:

        bool properlyInitialized();

        Logger *_initCheck;


    };

} // System

#endif //PROJSOFTENG_LOGGER_H
