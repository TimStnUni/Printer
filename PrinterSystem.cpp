//
// Created by stand on 26/04/2024.
//

#include "PrinterSystem.h"

#include <algorithm>


namespace System {

    PrinterSystem::PrinterSystem() {

        //system_scheduler.setSystem(this);
        _initcheck = this;
        ENSURE(properlyInitialized(), "System wasn't properly initialized");

    }

    bool PrinterSystem::readXML(const char *filename) {

        REQUIRE(properlyInitialized(), "System wasn't properly initialized when attempting to read an XML file");


        std::ofstream outFile; // Create an output file stream
        std::string f = filename;
        std::string outputFileName = f + ".txt";
        const char *outputFileNameChar = outputFileName.c_str();
        outFile.open(outputFileNameChar); // Open the file

        XMLParser tempXML(filename, outFile);

        //if parse is not successful return false





        if (!tempXML.isConsistent()) {


            logger.printConsistency(outFile);

            return false;
        }


        std::set<unsigned int> tempJobNrSet = tempXML.getJobNrSet();


        std::vector<unsigned int> testVector;

        std::set_intersection(jobNrSet.begin(), jobNrSet.end(), tempJobNrSet.begin(), tempJobNrSet.end(),
                              std::back_inserter(testVector));

        if (testVector.empty()) {


            jobNrSet.insert(tempJobNrSet.begin(), tempJobNrSet.end());


            std::vector<Device *> *tempDevs = tempXML.getDeviceList();
            std::vector<Job *> *tempJobs = tempXML.getJobList();

            deviceList.insert(deviceList.end(), tempDevs->begin(), tempDevs->end());
            jobList.insert(jobList.end(), tempJobs->begin(), tempJobs->end());

            jobsUnscheduledList.insert(jobsUnscheduledList.end(), tempJobs->begin(), tempJobs->end());

            this->scheduleAll(outFile);

            return true;
        }

        logger.printError(outFile, std::to_string(testVector.size()) + " Jobnrs was/were not unique, rejecting xml");


        outFile.close();
        return false;

    }

    void PrinterSystem::getInfo(std::ostream &writeStream, std::string outputType, bool advanced) {

        REQUIRE(properlyInitialized(), "the printer system was not properly initialized");

        InfoPrinter printer;
        printer.setSystem(this);

        if (!advanced) {
            if (outputType == "ASCII") {

                printer.printAscii(writeStream);
            } else {
                logger.printError(std::cerr, "Unsupported output type, reverting to ASCII");
                printer.printAscii(writeStream);
            }
        } else {
            if (outputType == "ASCII") {

                printer.printAdvancedAscii(writeStream);
            } else {
                logger.printError(std::cerr, "Unsupported output type, reverting to ASCII");
                printer.printAdvancedAscii(writeStream);
            }

        }


    }


    bool PrinterSystem::properlyInitialized() {
        return (this == _initcheck);
    }


    void PrinterSystem::doPrintJob(std::string deviceName, std::ostream &writestream, bool erasebool) {

        REQUIRE(properlyInitialized(), "system not properly initialized");
        REQUIRE(!deviceName.empty(), "device name should not be empty");

        for (std::list<Device *>::iterator devIt = deviceList.begin(); devIt != deviceList.end(); devIt++) {

            if ((*devIt)->getNameDev() == deviceName) {

                doPrintJob(*devIt, writestream, erasebool);


                return;

            }


        }

        logger.printError(writestream, "no device with that name found");

    }


    void PrinterSystem::doPrintJob(Device *indevice, std::ostream &writeStream, bool eraseBool) {


        REQUIRE(properlyInitialized(), "Printersystem not properly initialized");
        REQUIRE(indevice != nullptr, "Printer should not be a nullptr");


        Job *jobptr = indevice->getCurrentJob();

        int queusize = indevice->getJobs()->size();

        int newCO2 = indevice->printCurrentJob();

        std::string printType;

        if (jobptr->getType() == "bw") {
            printType = "black-and-white-printing ";
        } else if (jobptr->getType() == "color") {
            printType = "color-printing ";
        } else if (jobptr->getType() == "scan") {
            printType = "scanning ";
        }


        logger.dispPrintJob(writeStream, jobptr->getJobNr(), indevice->getNameDev(), jobptr->getUserName(), printType,
                            jobptr->getPageCount(), newCO2);

        //Increment CO2 emissions
        totalCO2_system += newCO2;

        ENSURE(indevice->getJobs()->size() + 1 == queusize, "Job was not correctly printed");

        if (eraseBool) {

            //Scheduler can't access anything anymore, so we remove jobs from the unscheduled list when we call it
            //Here jobs are removed from the list of jobs and the set of jobs, so the job must also be deleted.

            jobNrSet.erase(jobptr->getJobNr());
            this->removeJob(jobptr);
            //delete jobptr;

        }


    }


    void PrinterSystem::doPrintJobFull(Device *indevice, std::ostream &writestream, bool erasebool) {


        REQUIRE(properlyInitialized(), "system wasn't properly initialized");
        REQUIRE(indevice != nullptr, "Indevice should not be a nullptr");

        while (!indevice->getJobs()->empty()) {

            doPrintJob(indevice, writestream, erasebool);
        }

        ENSURE((*indevice->getJobs()).empty(), "jobs were not all executed");

    }


    void PrinterSystem::printAll(std::ostream &writeStream) {
        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to print all jobs");


        bool eraseBool = true;

        for (std::list<Device *>::iterator devIt = deviceList.begin();
             devIt != deviceList.end();) {


            this->doPrintJobFull(*devIt++, writeStream, eraseBool);

        }


        logger.printError(writeStream,
                          "Total CO2 emitted by jobs until now is " + std::to_string(totalCO2_system) + " gram");


        if (eraseBool) {
            ENSURE(jobList.empty(), "Jobs were not all correctly removed");
            ENSURE(jobNrSet.empty(), "Jobnrs were not correctly cleared");
        }

    }

    void PrinterSystem::addJob(Job *inJob) {

        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a job");

        this->jobList.push_back(inJob);
        ENSURE(jobList.back() == inJob, "Job was not correctly added");


    }

    void PrinterSystem::addDevice(Device *inDevice) {

        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a device");
        //REQUIRE(inDevice != nullptr, "input device should not be a nullptr");

        this->deviceList.push_back(inDevice);


        ENSURE(deviceList.back() == inDevice, "Device was not correctly added");


    }


    PrinterSystem::~PrinterSystem() {

        for (Device *dev: this->deviceList) {
            delete dev;
        }
        for (Job *job: this->jobList) {
            delete job;
        }


    }

    std::list<Device *> *PrinterSystem::getDeviceList() {
        REQUIRE(properlyInitialized(), "System not properly initialized");
        return &(deviceList);
    }


    void PrinterSystem::scheduleAll(std::ostream &errorstream) {

        REQUIRE(properlyInitialized(), "system not properly initialized when trying to schedule all jobs");


        if (!jobsUnscheduledList.empty()) {


            for (std::list<Job *>::iterator unsIt = jobsUnscheduledList.begin(); unsIt != jobsUnscheduledList.end();) {

                int retval = system_scheduler.schedule(*unsIt, &deviceList, errorstream);
                if (retval != 0) {

                    //this is removing jobs when no suitable devices are found.
                    jobNrSet.erase((*unsIt)->getJobNr());
                    removeJob(*unsIt);
                    //delete *unsIt;
                }
                //removeScheduled(*unsIt++);
                jobsUnscheduledList.erase(unsIt++);

            }
        }

        ENSURE(jobsUnscheduledList.empty(), "Not all jobs were correctly scheduled");

    }

    bool PrinterSystem::removeJob(Job *inJob) {

        REQUIRE(properlyInitialized(), "System wasn't properly initialized when attempting to remove a job");
        REQUIRE(inJob != nullptr, "Injob should not be a nullptr");

        for (std::list<Job *>::iterator jobIt = jobList.begin(); jobIt != jobList.end(); jobIt++) {

            if (*jobIt == inJob) {
                jobList.erase(jobIt);
                delete inJob;

                ENSURE(std::find(jobList.begin(), jobList.end(), inJob) == jobList.end(), "job not correclty removed");
                return true;

            }

        }


        return false;
    }


}



