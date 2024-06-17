//
// Created by stand on 26/04/2024.
//

#ifndef PROJSOFTENG_PRINTERSYSTEM_H
#define PROJSOFTENG_PRINTERSYSTEM_H

#include "Printer.h"
#include "XMLParser.h"

#include "Job.h"
#include "InfoPrinter.h"
#include "Scheduler.h"
#include "DesignByContract.h"

#include "Device.h"
#include "CPrinter.h"
#include "BWPrinter.h"
#include "Scanner.h"


namespace System {


    class PrinterSystem {

        //Todo: Remove friend classes
        friend class Device;
        friend class Scheduler;
        friend class InfoPrinter;

    public:
        //Should simply always be running, no input in constructor.

        /**
         * \brief Constructor for the printer system. Does not take any inputs, simply sets the system running.
         * ENSURE(properlyInitalized(), "System was not properly initialized")
         */
        PrinterSystem();


        /**
         * \brief Destructor for the printer system. Will delete all new'ed pointers
         */
        ~PrinterSystem();

        /**
         * \brief Reads an XML file and adds all devices/jobs inside to the printer system
         * @param filename XML file to read from
         * REQUIRE(properlyInitialized(), "System wasn't properly initialized when attempting to read an XML file")
         */
        bool readXML(const char *filename);


        /**
         * \brief Function that prints all known information about the printing system to a stream in a certain format
         * @param writestream stream to dump info into
         * @param outputType type of the output
         *REQUIRE(properlyInitialized(), "the printer system was not properly initialized")
         */
        void getInfo(std::ostream &writestream, std::string outputType);


        /**
         * \brief Function that executes a print job.
         * @param jobnr JobNr of the job to be executed
         * @param writeStream Stream where the output is stored
         * REQUIRE(properlyInitialized()
         */
        void doPrintJob(unsigned int jobnr, std::ostream &writeStream, bool erasebool = true);

        /**
         * \brief Loops over all jobs and prints that they are finished.
         * @param writeStream Stream where the output will be stored
         * REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to print all jobs");
         */

        void printAll(std::ostream &writeStream);


        /**
         * Adder function for a single job
         * @param inJob
         * REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to print add job");
         * ENSURE(jobVect.back() == inJob, "Job was not correctly added");
         */
        void addJob(Job *inJob);

        /**
         * adder function for a single device
         * @param inDevice
         * REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a device")
         * ENSURE(deviceVect.back == inDevice, "Device was not correctly added");
         */
        void addDevice(Device *inDevice);



        /**
         * \brief Function that takes input from the parsing. Currently still using an outdated plan for parser, but still works.
         * @param inDev Single inputdevice. Technically means we cannot read files with only jobs.
         * @param inJobs Vector of inputjobs. Handles 0 jobs just fine.
         * REQUIRE(properlyInitialized(), "System wasn't properly initialized when attempting to add devices and jobs")
         * ENSURE is handles by its subdivisions addDevice and addJob. Could change those functions to return a bool and
         * ENSURE that the sum of those bools is true or something
         */

        void takeParseInput(Device * inDev, std::vector<Job*>& inJobs);







    private:

        float totalCO2_system = 0;

        std::set<unsigned int> jobNrSet;
        std::vector<Job*> jobVect;


        std::vector<Device*> deviceVect;


        Scheduler system_scheduler;
        bool properlyInitialized();

        std::vector<Printer> printerList;
        PrinterSystem *_initcheck;
    };


} // System

#endif //PROJSOFTENG_PRINTERSYSTEM_H
