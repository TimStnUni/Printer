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





        //void getSystemGraph(std::ostream &writestream, std::string outputSys);


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
         * REQUIRE(properlyInitialized(), "Printersystem not properly initialized")
         * REQUIRE(indevice != nullptr, "Printer should not be a nullptr");
         * ENSURE(indevice->getJobs()->size()+1 == queusize, "Job was not correctly printed")
         */

        void doPrintJob(Device * inDevice, std::ostream &writeStream, bool erasebool = true);


        /**
         * \brief Function to print all jobs in a device's queue
         * @param inDevice
         * @param writesteram
         * @param erasebool
         * REQUIRE(properlyInitialized(), "system wasn't properly initialized")
         * REQUIRE(indevice != nullptr, "Indevice should not be a nullptr")
         *  ENSURE((*indevice->getJobs()).empty(), "jobs were not all executed");
         */
        void doPrintJobFull(Device * inDevice, std::ostream &writesteram, bool erasebool = true);



        /**
         * \brief Function that takes a devicename instead of a pointer for testing purposes
         * @param deviceName
         * @param writestream
         * @param erasebool
         * REQUIRE(properlyInitialized(), "system not properly initialized");
         * REQUIRE(!deviceName.empty(), "device name should not be empty");
         * ENSURE(indevice->getJobs()->size()+1 == queusize, "Job was not correctly printed") // Dit is eigenlijk slechts een wrapper over de gewone doprintjob
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
         * \brief Adder function for a single job
         * @param inJob
         * REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to print add job");
         * ENSURE(jobVect.back() == inJob, "Job was not correctly added");
         */
        void addJob(Job *inJob);

        /**
         * \brief adder function for a single device
         * @param inDevice
         * REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a device")
         * ENSURE(deviceVect.back == inDevice, "Device was not correctly added");
         */
        void addDevice(Device *inDevice);


        /**
         * \brief Function to schedule all jobs
         * REQUIRE(properlyInitialized(), "system not properly initialized when trying to schedule all jobs");
         * ENSURE(jobsUnscheduledVect.empty(), "Not all jobs were correctly scheduled");
         */

        void scheduleAll(std::ostream & errorstream);



        /**
         * \brief Function to remove a job from the system
         * @param inJob
         * @return
         * REQUIRE(properlyInitialized(), "System wasn't properly initialized when attempting to remove a job")
         * REQUIRE(inJob != nullptr, "Injob should not be a nullptr")
         * ENSURE(std::find(jobVect.begin(), jobVect.end(), inJob) == jobVect.end(), "job not correclty removed")
         */
        bool removeJob(Job * inJob);



        /**
         * \brief Function to get a pointer to the devicelist
         * @return
         * REQUIRE(properlyInitialized(), "System not properly initialized")
         */

        std::list<Device*> * getDeviceList();








    private:

        float totalCO2_system = 0;

        std::set<unsigned int> jobNrSet;

        std::list<Job*> jobsUnscheduledList;

        std::list<Job*> jobList;


        std::list<Device*> deviceList;


        Scheduler system_scheduler;
        bool properlyInitialized();

        Logger logger;

        PrinterSystem *_initcheck;


    };


} // System

#endif //PROJSOFTENG_PRINTERSYSTEM_H
