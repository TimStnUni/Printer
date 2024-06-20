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
        this->jobPtrQueue = inDevice.jobPtrQueue;


        /*
         * Pointer bullshittery that should no longer be needed
        for (std::vector<Job *>::const_iterator ptrIt = inDevice.jobPtrQueue.begin();
             ptrIt != inDevice.jobPtrQueue.end(); ++ptrIt) {
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

        this->jobPtrQueue.push_back(&*(ownSystem->jobVect.end() - 1));


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
        outDevice.jobPtrQueue = inDevice.jobPtrQueue;
        outDevice._initCheck = &outDevice;

        /*


         if (inDevice.jobPtrQueue.size()>0) {

            for (std::vector<Job *>::const_iterator ptrIt = inDevice.jobPtrQueue.begin();
                 ptrIt != inDevice.jobPtrQueue.end(); ++ptrIt) {
                (*ptrIt)->setOwnDevice(this);
            }
        }
         */
        return *this;
    }


/*
    void Device::updatePointer(Job *inPointer, const Job *prevPointer) {

        for (std::vector<Job *>::iterator ptrIt = this->jobPtrQueue.begin(); ptrIt != this->jobPtrQueue.end(); ++ptrIt) {

            if ((*ptrIt) == prevPointer) {
                *ptrIt = inPointer;
            }
        }


    }
    */

    void Device::removeJob() {

        REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to remove a job from queue");


        if (jobPtrQueue.empty()) {

            logger.printError(std::cout, "no jobs in queue");
            return;


        }

        int queuesize = jobPtrQueue.size();

        jobPtrQueue.pop_front();


        ENSURE(jobPtrQueue.size() + 1 == queuesize, "job was not properly removed from device");


    }

    int Device::getTotalPages() {


        REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to get total pages");

        int pages = 0;

        if (this->jobPtrQueue.size() > 0) {
            for (std::deque<Job *>::iterator jobIt = jobPtrQueue.begin(); jobIt != jobPtrQueue.end(); jobIt++) {
                pages += (*jobIt)->getRemainingPages();
            }
            return pages;
        } else {
            return 0;
        }


    }

    void Device::addJob(Job *jobIn) {

        REQUIRE(this->properlyInitialized(), "Device was not properly initialized when attempting to add a job");
        REQUIRE(jobIn != nullptr, "job should be a valid job");


        this->jobPtrQueue.push_back(jobIn);

        ENSURE(jobPtrQueue.back() == jobIn, "Job was not correctly added");

    }

    void Device::printAllJobs() {


        REQUIRE(properlyInitialized(), "device was not properly initialized when attepting to finish the queue");
        //I think this automatically checks that there is at least 1 job in the queue?

        while (!jobPtrQueue.empty()) {
            printCurrentJob();
        }

        ENSURE(jobPtrQueue.empty(), "Not all jobs were correctly printed");

    }

    /*
     * //Should be deprecated
    bool Device::printJob(Job *jobPtr) {


        REQUIRE(properlyInitialized(), "this printer was not properly initialized when calling printJob");
        REQUIRE(jobPtr != nullptr, "job should be a valid job");


        if (jobPtrQueue.size() != 0) {
            jobPtr->printFull();
            jobPtrQueue.erase(jobPtr);

            ENSURE(jobPtrQueue.count(jobPtr) == 0, "Job was not correctly removed");
            return true;
        }

        logger.printerAssignmentError(std::cout, jobPtr->getJobNr());

        return false;


    }
*/

    /*
     * should be deprecated
    void Device::printJob(unsigned int jobNr) {

        //todo: simplify function. This function should be removed anyway, so i'm not changing it

        for (std::unordered_set<Job *>::iterator jobIt = jobPtrQueue.begin(); jobIt != jobPtrQueue.end(); jobIt++) {

            if ((*jobIt)->getJobNr() == jobNr) {

                (*jobIt)->printFull();
                return;
            }

        }

        std::cout << "this job was not assigned to this printer." << std::endl;

    }
     */


    /*
     * should be deprecated
    bool Device::printJobPages(Job *jobPtr, unsigned int pages) {

        REQUIRE(properlyInitialized(), "this printer was not properly initialized when calling printJob");
        REQUIRE(jobPtr != nullptr, "job should be a valid job");
        REQUIRE(pages > 0, "Pages to be printed should be positive");

        if (jobPtrQueue.count(jobPtr) != 0) {

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
     */

    /*
     * should be deprecated
    void Device::printJobPages(unsigned int jobNr, unsigned int pages) {

        //todo: simplify function. This function should be removed anyways so i'm not changing it

        for (std::unordered_set<Job *>::iterator jobIt = jobPtrQueue.begin(); jobIt != jobPtrQueue.end(); jobIt++) {

            if ((*jobIt)->getJobNr() == jobNr) {

                (*jobIt)->printPages(pages);
                return;
            }

        }

        logger.printerAssignmentError(std::cout, jobNr);

    }

     */


    int Device::printCurrentJob() {

        REQUIRE(properlyInitialized(), "printer not properly initialized when calling printcurrentjob");
        //Not sure if this should be a require?
        REQUIRE(!jobPtrQueue.empty(), "There should be at least 1 job in the queue");


        int co2 = jobPtrQueue.front()->printFull();

        int queuesize = jobPtrQueue.size();
        jobPtrQueue.pop_front();

        ENSURE(jobPtrQueue.size() + 1 == queuesize, "Job was not correctly removed");

        return co2;


    }

    int Device::printCurrentJobPages(unsigned int pages) {

        REQUIRE(properlyInitialized(), "printer not properly initialized when calling printcurrentjob");
        REQUIRE(!jobPtrQueue.empty(), "There should be at least 1 job in the queue");

        if (pages < jobPtrQueue.front()->getRemainingPages() ) {

            return jobPtrQueue.front()->printPages(pages);
        }

        logger.pageAmount(std::cout);
        int co2 = jobPtrQueue.front()->printFull();
        int queuesize = jobPtrQueue.size();

        jobPtrQueue.pop_front();

        ENSURE(jobPtrQueue.size() +1 == queuesize, "job was not correctly removed");

        return co2;


    }

    bool Device::belowLimit() {
        return false;
    }

    std::deque<Job *> *Device::getJobs() {
        return &jobPtrQueue;
    }

    Job *Device::getCurrentJob() {
        return jobPtrQueue.front();
    }


} // System