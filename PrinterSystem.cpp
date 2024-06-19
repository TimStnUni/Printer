//
// Created by stand on 26/04/2024.
//

#include "PrinterSystem.h"

//todo: add ways to delete jobs and devices

namespace System {

    PrinterSystem::PrinterSystem() {

        system_scheduler.setSystem(this);
        _initcheck = this;
        ENSURE(properlyInitialized(), "System wasn't properly initialized");

    }

    bool PrinterSystem::readXML(const char *filename) {

        REQUIRE(properlyInitialized(), "System wasn't properly initialized when attempting to read an XML file");

        XMLParser tempXML(filename, this);

        //if parse is not successful return false
        if (!tempXML.isParseSuccessful()) {
            return false;
        }



        std::set<unsigned int> tempJobSet = tempXML.getJobNrSet();

        for (std::set<unsigned int>::iterator it = tempJobSet.begin(); it != tempJobSet.end(); ++it) {

            if (jobNrSet.find(*it) == jobNrSet.end()) {
                jobNrSet.insert(*it);

            } else {
                //todo : Expand on this error
                std::cout << "JobNr is not unique" << std::endl;
            }

        }


        return true;

    }

    void PrinterSystem::getInfo(std::ostream &writeStream, std::string outputType) {

        REQUIRE(properlyInitialized(), "the printer system was not properly initialized");


        for (std::set<unsigned int>::reverse_iterator jobnrIt = jobNrSet.rbegin();
             jobnrIt != jobNrSet.rend(); jobnrIt++) {

            for (std::set<Job *>::iterator jobsIt = jobVect.begin(); jobsIt != jobVect.end(); jobsIt++) {

                if ((*jobsIt)->getJobNr() == *jobnrIt) {
                    system_scheduler.schedule(*jobsIt, &deviceVect);
                }
            }

        }


        InfoPrinter printer;
        printer.setSystem(this);


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

        Job * jobptr = nullptr;


        for (std::set<Job *>::iterator jobIt = this->jobVect.begin(); jobIt != this->jobVect.end(); ++jobIt) {
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


        if (this->jobNrSet.find(jobptr->getJobNr()) != jobNrSet.end()) {
            //todo: change this implementation
            //This means the job has not yet been scheduled
            system_scheduler.schedule(jobptr, &deviceVect);
        }


        Device *printPoint = jobptr->getOwnDevice();


        int pages = jobptr->getPageCount();


        while (pages > 0) {
            pages--;
        }


        std::string printType;

        if (jobptr->getType() == "bw") {
            printType = "black-and-white-printing ";
        } else if (jobptr->getType() == "color") {
            printType = "color-printing ";
        } else if (jobptr->getType() == "scan") {
            printType = "scanning ";
        }

        writeStream << "Printer \"" << printPoint->getNameDev() << "\" finished " << printType << "job:\n";
        writeStream << "  Number: " << jobptr->getJobNr() << "\n";
        writeStream << "  Submitted by \"" << jobptr->getUserName() << "\"\n";
        writeStream << "  " << jobptr->getPageCount() << " pages\n";


        float newCO2 = (float)(jobptr->getPageCount()) * (float)(printPoint->getEmissions());

        writeStream << "  Job CO2 emissions: " << newCO2 << " gram\n";
        writeStream << std::endl;

        //Increment CO2 emissions
        totalCO2_system += newCO2;

        //std::cout << "total CO2 emissions for now " << totalCO2_system << std::endl;

        if (eraseBool) {

            // Remove the job number from the jobNrSet and jobNrMap
            //This is now already done in scheduler
            //I think this should only be done here
            jobNrSet.erase(jobptr->getJobNr());

            //TODO: Figure out why erasing seems to miss.
            //jobVect.erase(jobPoint);
            jobptr->getOwnDevice()->removeJob(jobptr);
        }
    }


    void PrinterSystem::printAll(std::ostream &writeStream) {
        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to print all jobs");


        for (std::set<unsigned int>::reverse_iterator jobNrIt = jobNrSet.rbegin();
             jobNrIt != jobNrSet.rend(); jobNrIt++) {


            //Erasing jobnr's is having issues
            this->doPrintJob(*jobNrIt, writeStream, false);

        }


        writeStream << "Total CO2 emitted by jobs until now is " << totalCO2_system << " gram" << std::endl;

    }

    void PrinterSystem::addJob(Job *inJob) {

        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a job");

        this->jobVect.insert(inJob);


        ENSURE(jobVect.count(inJob) !=0, "Job was not correctly added");


    }

    void PrinterSystem::addDevice(Device *inDevice) {

        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a device");
        //REQUIRE(inDevice != nullptr, "input device should not be a nullptr");

        this->deviceVect.insert(inDevice);


        ENSURE(deviceVect.count(inDevice) != 0, "Device was not correctly added");


    }



    PrinterSystem::~PrinterSystem() {

        for (Device * dev: this->deviceVect) {
            delete dev;
        }
        for (Job * job: this->jobVect) {
            delete job;
        }


    }

    std::set<Device *> *PrinterSystem::getDeviceVector() {
        return &(deviceVect);
    }

    std::set<Job *> *PrinterSystem::getJobVector() {
        return &(jobVect);
    }

    void PrinterSystem::testPrinting() {


        std::cout << (*this->deviceVect.begin())->jobPtrSet.size() << std::endl;

        (*this->deviceVect.begin())->printAllJobs();

    }




}



