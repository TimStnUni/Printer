//
// Created by tim on 18/04/24.
//

#include "Device.h"
#include "Job.h"
//#include "PrinterSystem.h"


namespace System {


    Device::Device(std::string name_in, int emissions_in, int speed_in, std::string type_in, float cost_in) {
        REQUIRE(emissions_in > 0, "Emissions should be positive");
        REQUIRE(speed_in > 0, "Speed should be positive");
        REQUIRE(!type_in.empty(), "type should not be blank");
        REQUIRE(cost_in > 0, "Cost should be positive");
        REQUIRE(!(name_in.empty()), "name shouldn't be empty");
        _initCheck = this;


        this->setNameDev(name_in);
        this->setEmissions(emissions_in);
        this->setSpeed(speed_in);
        this->setType(type_in);
        this->setCost(cost_in);

        ENSURE(this->properlyInitialized(), "Device is not properly initialized");
    }

    Device::Device() {
        _initCheck = this;

        ENSURE(this->properlyInitialized(), "device was not properly initialized in the default constructor");

    }

    std::string Device::getNameDev() const {

        REQUIRE(this->properlyInitialized(), "Device not initialized when calling getNameDev()");
        return name;
    }

    int Device::getEmissions() const {
        REQUIRE(this->properlyInitialized(), "Device not initialized when calling getEmissions()");
        return emissions;
    }

    int Device::getSpeed() const {
        REQUIRE(this->properlyInitialized(), "Device not initialized when calling getSpeed()");
        return speed;
    }

    std::string Device::getType() const {

        REQUIRE(this->properlyInitialized(), "Device not initialized when calling getType()");
        return type;
    }

    float Device::getCost() const {

        REQUIRE(this->properlyInitialized(), "Device not initialized when calling getCost()");
        return cost;
    }

    bool Device::properlyInitialized() const {
        return (_initCheck == this);
    }

    Device::Device(const Device &inDevice) {


        _initCheck = this;


        std::string inName = inDevice.getNameDev();

        int emissions_in = inDevice.getEmissions();
        int speed_in = inDevice.getSpeed();
        std::string type_in = inDevice.getType();
        float cost_in = inDevice.getCost();


        this->setNameDev(inName);
        this->setEmissions(emissions_in);
        this->setSpeed(speed_in);
        this->setType(type_in);
        this->setCost(cost_in);
        this->jobPtrSet = inDevice.jobPtrSet;


        /*
         * Pointer bullshittery that should no longer be needed
        for (std::vector<Job *>::const_iterator ptrIt = inDevice.jobPtrSet.begin();
             ptrIt != inDevice.jobPtrSet.end(); ++ptrIt) {
            (*ptrIt)->setOwnDevice(this);
        }
        */

        ENSURE(this->properlyInitialized(), "Device not properly initialized in copy constructor");


    }

    void Device::setNameDev(std::string &inName) {

        REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to set name");
        REQUIRE(!(inName.empty()), "name shouldn't be empty");
        this->name = inName;

        ENSURE(this->getNameDev() == inName, "Name not correctly set");

    }

    void Device::setEmissions(int &emissions_in) {

        REQUIRE(emissions_in > 0, "Emissions should be positive");
        REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to set emissions");
        this->emissions = emissions_in;
        ENSURE(this->getEmissions() == emissions_in, "Emissions not correctly set");

    }

    void Device::setSpeed(int &speed_in) {

        REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to set speed");
        REQUIRE(speed_in > 0, "Speed should be positive");

        this->speed = speed_in;

        ENSURE(this->getSpeed() == speed_in, "Speed not correctly set");

    }

    void Device::setType(std::string &type_in) {
        REQUIRE(!type_in.empty(), "Type shouldn't be empty");
        REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to set type");
        this->type = type_in;
        ENSURE(this->getType() == type_in, "Type not correctly set");
    }

    void Device::setCost(float &cost_in) {
        REQUIRE(cost_in >= 0, "Cost should be positive");
        REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to set cost");
        this->cost = cost_in;
        ENSURE(this->getCost() == cost_in, "Cost not correctly set");
    }


    /*
    void Device::addJob(PrinterSystem *ownSystem) {

        this->jobPtrSet.push_back(&*(ownSystem->jobVect.end() - 1));


    }
     */

    Device &Device::operator=(const Device &inDevice) {


        std::cout << "using the operator " << std::endl;

        Device outDevice;
        outDevice.name = inDevice.getNameDev();
        outDevice.emissions = inDevice.getEmissions();
        outDevice.speed = inDevice.getSpeed();
        outDevice.cost = inDevice.getCost();
        outDevice.type = inDevice.getType();
        outDevice.jobPtrSet = inDevice.jobPtrSet;
        outDevice._initCheck = &outDevice;

        /*


         if (inDevice.jobPtrSet.size()>0) {

            for (std::vector<Job *>::const_iterator ptrIt = inDevice.jobPtrSet.begin();
                 ptrIt != inDevice.jobPtrSet.end(); ++ptrIt) {
                (*ptrIt)->setOwnDevice(this);
            }
        }
         */
        return *this;
    }


/*
    void Device::updatePointer(Job *inPointer, const Job *prevPointer) {

        for (std::vector<Job *>::iterator ptrIt = this->jobPtrSet.begin(); ptrIt != this->jobPtrSet.end(); ++ptrIt) {

            if ((*ptrIt) == prevPointer) {
                *ptrIt = inPointer;
            }
        }


    }
    */

    void Device::removeJob(Job *jobptr) {

        REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to remove a job from queu");
        REQUIRE(jobptr != nullptr, "job should be a valid job");

        if (jobPtrSet.count(jobptr)) {
            jobPtrSet.erase(jobptr);
        } else {

            logger.printerAssignmentError(std::cout, jobptr->getJobNr());
        }


        ENSURE(jobPtrSet.count(jobptr) == 0, "job was not properly removed from device");


    }

    int Device::getTotalPages() {

        REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to get total pages");

        int pages = 0;

        if (this->jobPtrSet.size() > 0) {
            for (std::set<Job *>::iterator jobIt = jobPtrSet.begin(); jobIt != jobPtrSet.end(); jobIt++) {
                pages += (*jobIt)->getPageCount();
            }
            return pages;
        } else {
            return 0;
        }


    }

    void Device::addJob(Job *jobIn) {

        REQUIRE(this->properlyInitialized(), "Device was not properly initialized when attempting to add a job");
        REQUIRE(jobIn != nullptr, "job should be a valid job");


        this->jobPtrSet.insert(jobIn);

        ENSURE(jobPtrSet.count(jobIn) == 1, "Job was not correctly added");

    }

    void Device::printAllJobs() {


        REQUIRE(properlyInitialized(), "device was not properly initialized when attepting to finish the queue");
        //I think this automatically checks that there is at least 1 job in the queue?
        std::set<Job *>::iterator jobIt = jobPtrSet.begin();

        while (!jobPtrSet.empty()) {
            printCurrentJob();
        }

        ENSURE(jobPtrSet.empty(), "Not all jobs were correctly printed");

    }

    bool Device::printJob(Job *jobPtr) {


        REQUIRE(properlyInitialized(), "this printer was not properly initialized when calling printJob");
        REQUIRE(jobPtr != nullptr, "job should be a valid job");


        if (jobPtrSet.count(jobPtr) != 0) {
            jobPtr->printFull();
            jobPtrSet.erase(jobPtr);

            ENSURE(jobPtrSet.count(jobPtr) == 0, "Job was not correctly removed");
            return true;
        }

        logger.printerAssignmentError(std::cout, jobPtr->getJobNr());

        return false;


    }


    void Device::printJob(unsigned int jobNr) {

        //todo: simplify function. This function should be removed anyway, so i'm not changing it

        for (std::set<Job *>::iterator jobIt = jobPtrSet.begin(); jobIt != jobPtrSet.end(); jobIt++) {

            if ((*jobIt)->getJobNr() == jobNr) {

                (*jobIt)->printFull();
                return;
            }

        }

        std::cout << "this job was not assigned to this printer." << std::endl;

    }

    bool Device::printJobPages(Job *jobPtr, unsigned int pages) {

        REQUIRE(properlyInitialized(), "this printer was not properly initialized when calling printJob");
        REQUIRE(jobPtr != nullptr, "job should be a valid job");
        REQUIRE(pages > 0, "Pages to be printed should be positive");


        if (jobPtrSet.count(jobPtr) != 0) {

            if (pages < jobPtr->getRemainingPages()) {

                jobPtr->printPages(pages);
                return true;
            } else {
                return printJob(jobPtr);
            }
        }



        logger.printerAssignmentError(std::cout, jobPtr->getJobNr());
        return false;

    }

    void Device::printJobPages(unsigned int jobNr, unsigned int pages) {

        //todo: simplify function. This function should be removed anyways so i'm not changing it

        for (std::set<Job *>::iterator jobIt = jobPtrSet.begin(); jobIt != jobPtrSet.end(); jobIt++) {

            if ((*jobIt)->getJobNr() == jobNr) {

                (*jobIt)->printPages(pages);
                return;
            }

        }

        logger.printerAssignmentError(std::cout, jobNr);

    }

    bool Device::printCurrentJob() {

        REQUIRE(properlyInitialized(), "printer not properly initialized when calling printcurrentjob");
        REQUIRE(!jobPtrSet.empty(), "There should be at least 1 job in the queue");


        bool printed = this->printJob(*jobPtrSet.begin());
        ENSURE(printed, "Job was not correctly printed");
        return printed;

    }

    bool Device::printCurrentJobPages(unsigned int pages) {

        REQUIRE(properlyInitialized(), "printer not properly initialized when calling printcurrentjob");
        REQUIRE(!jobPtrSet.empty(), "There should be at least 1 job in the queue");

        bool printed = this->printJobPages(*jobPtrSet.begin(), pages);

        ENSURE(printed, "job was not correctly printed");
        return printed;



    }


} // System