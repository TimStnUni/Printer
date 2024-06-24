//
// Created by stand on 26/04/2024.
//

#ifndef PROJSOFTENG_PRINTERSYSTEM_H
#define PROJSOFTENG_PRINTERSYSTEM_H

//#include "Printer.h"
#include "XMLParser.h"

#include "Job.h"
#include "CJob.h"
#include "BWJob.h"
#include "ScanJob.h"

#include "Device.h"
#include "CPrinter.h"
#include "BWPrinter.h"
#include "Scanner.h"

#include "InfoPrinter.h"
#include "Scheduler.h"
#include "Logger.h"

#include "DesignByContract.h"

#include <list>

namespace System {


    class PrinterSystem {

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
        void getInfo(std::ostream &writestream, std::string outputType, bool advanced);





        void getSystemGraph(std::ostream &writestream, std::string outputSys);


        /**
         * \brief Function that executes a print job via jobnr for testing, should be deprecated.
         * @param jobnr JobNr of the job to be executed
         * @param writeStream Stream where the output is stored
         * REQUIRE(properlyInitialized()
         */
        //void doPrintJob(unsigned int jobnr, std::ostream &writeStream, bool erasebool = true);


        /**
         * \brief Function that executes a print job via jobPtr.
         * @param jobnr JobNr of the job to be executed
         * @param writeStream Stream where the output is stored
         * REQUIRE(properlyInitialized()
         * ENSURE(job is removed)
         */

        void doPrintJob(Device * inDevice, std::ostream &writeStream, bool erasebool = true);


        void doPrintJobFull(Device * inDevice, std::ostream &writesteram, bool reasebool = true);



        /**
         * \brief Function that takes a devicename instead of a pointer for testing purposes
         *
         * @param deviceName
         * @param writestream
         * @param erasebool
         */

        void doPrintJob(std::string deviceName, std::ostream &writestream, bool erasebool = true);

        /**
         * \brief Loops over all jobs and prints that they are finished.
         * @param writeStream Stream where the output will be stored
         * REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to print all jobs");
         * ENSURE(jobVect.empty(), "Jobs were not all correctly removed");
         * ENSURE(jobNrSet.empty(), "Jobnrs were not correctly cleared");
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
         * Function to schedule all jobs
         * REQUIRE(properlyInitialized(), "system not properly initialized when trying to schedule all jobs");
         * ENSURE(jobsUnscheduledVect.empty(), "Not all jobs were correctly scheduled");
         */

        void scheduleAll();

        void testPrinting();


        bool removeJob(Job * inJob);

        bool removeDevice(Device * inDevice);

        bool removeScheduled(Job * inJob);


        std::list<Device*> * getDeviceVector();

        std::list<Job*> * getJobVector();


        void setStream(std::ostream * inStream);



    private:

        float totalCO2_system = 0;

        std::set<unsigned int> jobNrSet;

        std::list<Job*> jobsUnscheduledVect;

        std::list<Job*> jobVect;


        std::list<Device*> deviceVect;


        Scheduler system_scheduler;
        bool properlyInitialized();

        Logger logger;

        PrinterSystem *_initcheck;

        std::ostream * outStream = nullptr;
    };


} // System

#endif //PROJSOFTENG_PRINTERSYSTEM_H
