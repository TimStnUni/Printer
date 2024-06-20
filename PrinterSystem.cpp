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

        XMLParser tempXML(filename);

        //if parse is not successful return false
        if (!tempXML.isConsistent()) {


            logger.printConsistency(std::cerr);

            return false;
        }


        std::set<unsigned int> tempJobNrSet = tempXML.getJobNrSet();


        std::vector<unsigned int> testVector;

        std::set_intersection(jobNrSet.begin(), jobNrSet.end(), tempJobNrSet.begin(), tempJobNrSet.end(),
                              std::back_inserter(testVector));

        if (testVector.empty()) {


            jobNrSet.insert(tempJobNrSet.begin(), tempJobNrSet.end());


            std::unordered_set<Device *> *tempDevs = tempXML.getDeviceList();
            std::unordered_set<Job *> *tempJobs = tempXML.getJobList();

            deviceVect.insert(tempDevs->begin(), tempDevs->end());
            jobVect.insert(tempJobs->begin(), tempJobs->end());

            jobUnscheduled.insert(tempJobs->begin(), tempJobs->end());

            return true;
        }

        std::cerr << testVector.size() << " Jobnrs was/were not unique, rejecting xml" << std::endl;
        return false;

    }

    void PrinterSystem::getInfo(std::ostream &writeStream, std::string outputType) {

        REQUIRE(properlyInitialized(), "the printer system was not properly initialized");


        for (std::set<Job *>::iterator jobsIt = jobUnscheduled.begin(); jobsIt != jobUnscheduled.end(); jobsIt++) {


            system_scheduler.schedule(*jobsIt, &deviceVect);
            jobUnscheduled.erase(*jobsIt);

        }


        InfoPrinter printer;


        if (outputType == "ASCII") {

            printer.printAscii(writeStream);
        } else {
            std::cerr << "Unsupported output type, reverting to ASCII" << std::endl;
            printer.printAscii(writeStream);
        }


    }

    bool PrinterSystem::properlyInitialized() {
        return (this == _initcheck);
    }


    void PrinterSystem::doPrintJob(unsigned int jobNr, std::ostream &writeStream, bool eraseBool) {

        Job *jobptr = nullptr;


        for (std::unordered_set<Job *>::iterator jobIt = this->jobVect.begin(); jobIt != this->jobVect.end(); ++jobIt) {
            if ((*jobIt)->getJobNr() == jobNr) {
                jobptr = *jobIt;
                break;
            }
            if (jobIt == (this->jobVect.end())) {
                std::cerr << "JobNr not found" << std::endl;
                return;
            }
        }


        this->doPrintJob(jobptr, writeStream, eraseBool);


    }

    void PrinterSystem::doPrintJob(Job *jobptr, std::ostream &writeStream, bool eraseBool) {


        if (this->jobUnscheduled.count(jobptr) != 0) {
            //This means the job has not yet been scheduled
            system_scheduler.schedule(jobptr, &deviceVect);
            jobUnscheduled.erase(jobptr);
        }


        Device *printPoint = jobptr->getOwnDevice();

        int newCO2 = jobptr->printFull();

        std::string printType;

        if (jobptr->getType() == "bw") {
            printType = "black-and-white-printing ";
        } else if (jobptr->getType() == "color") {
            printType = "color-printing ";
        } else if (jobptr->getType() == "scan") {
            printType = "scanning ";
        }


        logger.dispPrintJob(writeStream, jobptr->getJobNr(), printPoint->getNameDev(), jobptr->getUserName(), printType,
                            jobptr->getPageCount(), newCO2);

        //Increment CO2 emissions
        totalCO2_system += newCO2;

        //std::cout << "total CO2 emissions for now " << totalCO2_system << std::endl;

        if (eraseBool) {

            //Scheduler can't access anything anymore, so we remove jobs from the unscheduled list when we call it
            //Here jobs are removed from the list of jobs and the set of jobs, so the job must also be deleted.

            jobNrSet.erase(jobptr->getJobNr());
            jobVect.erase(jobptr);
            delete jobptr;

        }
    }


    void PrinterSystem::printAll(std::ostream &writeStream) {
        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to print all jobs");

        //For some reason this breaks the debugger, So i guess i'm creating a pointer pointing nowhere somewhere?
        this->scheduleAll();

        bool eraseBool = true;

        for (std::unordered_set<Job *>::iterator jobNrIt = jobVect.begin();
             jobNrIt != jobVect.end();) {


            //Erasing jobnr's is having issues
            this->doPrintJob(*jobNrIt++, writeStream, eraseBool);

        }


        writeStream << "Total CO2 emitted by jobs until now is " << totalCO2_system << " gram" << std::endl;

        if (eraseBool) {
            ENSURE(jobVect.empty(), "Jobs were not all correctly removed");
            ENSURE(jobNrSet.empty(), "Jobnrs were not correctly cleared");
        }

    }

    void PrinterSystem::addJob(Job *inJob) {

        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a job");

        this->jobVect.insert(inJob);


        ENSURE(jobVect.count(inJob) != 0, "Job was not correctly added");


    }

    void PrinterSystem::addDevice(Device *inDevice) {

        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a device");
        //REQUIRE(inDevice != nullptr, "input device should not be a nullptr");

        this->deviceVect.insert(inDevice);


        ENSURE(deviceVect.count(inDevice) != 0, "Device was not correctly added");


    }


    PrinterSystem::~PrinterSystem() {

        for (Device *dev: this->deviceVect) {
            delete dev;
        }
        for (Job *job: this->jobVect) {
            delete job;
        }


    }

    std::unordered_set<Device *> *PrinterSystem::getDeviceVector() {
        return &(deviceVect);
    }

    std::unordered_set<Job *> *PrinterSystem::getJobVector() {
        return &(jobVect);
    }

    void PrinterSystem::testPrinting() {


        std::cout << (*this->deviceVect.begin())->jobPtrSet.size() << std::endl;

        (*this->deviceVect.begin())->printAllJobs();

    }

    void PrinterSystem::scheduleAll() {

        REQUIRE(properlyInitialized(), "system not properly initialized when trying to schedule all jobs");


        if (!jobUnscheduled.empty()) {

            for (std::set<Job *>::iterator unsIt = jobUnscheduled.begin(); unsIt != jobUnscheduled.end(); unsIt++) {

                system_scheduler.schedule(*unsIt, &deviceVect);
                jobUnscheduled.erase(unsIt);

            }
        }
        ENSURE(jobUnscheduled.empty(), "Not all jobs were correctly scheduled");

    }


}



