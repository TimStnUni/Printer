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


            std::vector<Device *> *tempDevs = tempXML.getDeviceList();
            std::vector<Job *> *tempJobs = tempXML.getJobList();

            deviceVect.insert(deviceVect.end(), tempDevs->begin(), tempDevs->end());
            jobVect.insert(jobVect.end(), tempJobs->begin(), tempJobs->end());

            jobsUnscheduledVect.insert(jobsUnscheduledVect.end(), tempJobs->begin(), tempJobs->end());

            this->scheduleAll();

            return true;
        }

        std::cerr << testVector.size() << " Jobnrs was/were not unique, rejecting xml" << std::endl;
        return false;

    }

    void PrinterSystem::getInfo(std::ostream &writeStream, std::string outputType, bool advanced) {

        REQUIRE(properlyInitialized(), "the printer system was not properly initialized");



        //todo: replace with scheduleall
        for (std::list<Job *>::iterator jobsIt = jobsUnscheduledVect.begin(); jobsIt != jobsUnscheduledVect.end(); jobsIt++) {

            if (!system_scheduler.schedule(*jobsIt, &deviceVect)){

                //this is removing the job when no suitable device is found;
                jobNrSet.erase((*jobsIt)->getJobNr());
                removeJob(*jobsIt);
                delete *jobsIt;
            }

            removeScheduled(*jobsIt);

        }


        //scheduleAll();


        InfoPrinter printer;
        printer.setSystem(this);

        if (!advanced) {
            if (outputType == "ASCII") {

                printer.printAscii(writeStream);
            } else {
                std::cerr << "Unsupported output type, reverting to ASCII" << std::endl;
                printer.printAscii(writeStream);
            }
        }else{
            if (outputType == "ASCII") {

                printer.printAdvancedAscii(writeStream);
            } else {
                std::cerr << "Unsupported output type, reverting to ASCII" << std::endl;
                printer.printAdvancedAscii(writeStream);
            }

        }


    }






    bool PrinterSystem::properlyInitialized() {
        return (this == _initcheck);
    }


    /*
    void PrinterSystem::doPrintJob(unsigned int jobNr, std::ostream &writeStream, bool eraseBool) {

        Job *jobptr = nullptr;


        for (std::vector<Job *>::iterator jobIt = this->jobVect.begin(); jobIt != this->jobVect.end(); ++jobIt) {
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
     */




    void PrinterSystem::doPrintJob(std::string deviceName, std::ostream &writestream, bool erasebool) {

        REQUIRE(properlyInitialized(), "system not properly initialized");
        REQUIRE(!deviceName.empty(), "device name should not be empty");

        for (std::list<Device *>::iterator devIt = deviceVect.begin(); devIt != deviceVect.end(); devIt++){

            if ((*devIt)->getNameDev() == deviceName){

                doPrintJob(*devIt, writestream, erasebool);

                //todo: add ensures and stuff
                return;

            }


        }

        logger.printError(writestream, "no device with that name found");

    }


    void PrinterSystem::doPrintJob(Device * indevice, std::ostream &writeStream, bool eraseBool) {


        /*

        if (std::find(this->jobsUnscheduledVect.begin(), this->jobsUnscheduledVect.end(), jobptr != 0) {
            //This means the job has not yet been scheduled
            if (!system_scheduler.schedule(jobptr, &deviceVect)){
                jobNrSet.erase(jobptr->getJobNr());
                jobVect.erase(jobptr);
                delete jobptr;

            }
            jobsUnscheduledVect.erase(jobptr);
        }

         */
        //this->scheduleAll();


        Job *jobptr = indevice->getCurrentJob();

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

        //std::cout << "total CO2 emissions for now " << totalCO2_system << std::endl;

        if (eraseBool) {

            //Scheduler can't access anything anymore, so we remove jobs from the unscheduled list when we call it
            //Here jobs are removed from the list of jobs and the set of jobs, so the job must also be deleted.

            jobNrSet.erase(jobptr->getJobNr());
            this->removeJob(jobptr);
            //delete jobptr;

        }
    }


    void PrinterSystem::doPrintJobFull(Device *indevice, std::ostream &writestream, bool reasebool) {


        REQUIRE(properlyInitialized(), "system wasn't properly initialized");

        this->scheduleAll();

        while(!indevice->getJobs()->empty()) {

            doPrintJob(indevice, writestream, reasebool);
        }

        ENSURE((*indevice->getJobs()).empty(), "jobs were not all executed");

    }


    void PrinterSystem::printAll(std::ostream &writeStream) {
        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to print all jobs");

        //For some reason this breaks the debugger, So i guess i'm creating a pointer pointing nowhere somewhere?
        this->scheduleAll();

        bool eraseBool = true;

        for (std::list<Device *>::iterator devIt = deviceVect.begin();
             devIt != deviceVect.end();) {



            this->doPrintJobFull(*devIt++, writeStream, eraseBool);

        }


        writeStream << "Total CO2 emitted by jobs until now is " << totalCO2_system << " gram" << std::endl;

        if (eraseBool) {
            ENSURE(jobVect.empty(), "Jobs were not all correctly removed");
            ENSURE(jobNrSet.empty(), "Jobnrs were not correctly cleared");
        }

    }

    void PrinterSystem::addJob(Job *inJob) {

        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a job");

        this->jobVect.push_back(inJob);
        ENSURE(jobVect.back() == inJob, "Job was not correctly added");



    }

    void PrinterSystem::addDevice(Device *inDevice) {

        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a device");
        //REQUIRE(inDevice != nullptr, "input device should not be a nullptr");

        this->deviceVect.push_back(inDevice);


        ENSURE(deviceVect.back() == inDevice, "Device was not correctly added");


    }


    PrinterSystem::~PrinterSystem() {

        for (Device *dev: this->deviceVect) {
            delete dev;
        }
        for (Job *job: this->jobVect) {
            delete job;
        }


    }

    std::list<Device *> *PrinterSystem::getDeviceVector() {
        return &(deviceVect);
    }

    std::list<Job *> *PrinterSystem::getJobVector() {
        return &(jobVect);
    }

    void PrinterSystem::testPrinting() {


        std::cout << (*this->deviceVect.begin())->jobPtrQueue.size() << std::endl;

        (*this->deviceVect.begin())->printAllJobs();

    }

    void PrinterSystem::scheduleAll() {

        REQUIRE(properlyInitialized(), "system not properly initialized when trying to schedule all jobs");


        if (!jobsUnscheduledVect.empty()) {



            for (std::list<Job *>::iterator unsIt = jobsUnscheduledVect.begin(); unsIt != jobsUnscheduledVect.end();) {

                if (!system_scheduler.schedule(*unsIt, &deviceVect, outStream)) {

                    //this is removing jobs when no suitable devices are found.
                    jobNrSet.erase((*unsIt)->getJobNr());
                    removeJob(*unsIt);
                    //delete *unsIt;
                }
                //removeScheduled(*unsIt++);
                jobsUnscheduledVect.erase(unsIt++);

            }
        }

        ENSURE(jobsUnscheduledVect.empty(), "Not all jobs were correctly scheduled");

    }

    bool PrinterSystem::removeJob(Job *inJob) {


        for (std::list<Job*>::iterator jobIt = jobVect.begin(); jobIt != jobVect.end(); jobIt++){

            if (*jobIt == inJob){
                jobVect.erase(jobIt);
                delete inJob;
                return true;

            }

        }


        return false;
    }

    bool PrinterSystem::removeDevice(Device *inDevice) {

        for (std::list<Device*>::iterator deviceIt = deviceVect.begin(); deviceIt != deviceVect.end(); deviceIt++){

            if (*deviceIt == inDevice){
                deviceVect.erase(deviceIt);
                return true;

            }

        }


        return false;
        
        
    }

    bool PrinterSystem::removeScheduled(Job *inJob) {
        for (std::list<Job*>::iterator jobIt = jobsUnscheduledVect.begin(); jobIt != jobsUnscheduledVect.end(); jobIt++){

            if (*jobIt == inJob){
                jobsUnscheduledVect.erase(jobIt);
                return true;

            }

        }


        return false;
    }

    void PrinterSystem::setStream(std::ostream *inStream) {


        outStream = inStream;

    }


}



