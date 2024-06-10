//
// Created by tim on 18/04/24.
//

#include "Device.h"
#include "Job.h"
#include "PrinterSystem.h"

namespace System {


    Device::Device(std::string name_in, int emissions_in, int speed_in, std::string type_in, float cost_in) {
        REQUIRE(emissions_in > 0, "Emissions should be positive");
        REQUIRE(speed_in > 0, "Speed should be positive");
        REQUIRE(!type_in.empty(), "type should not be blank");
        REQUIRE(cost_in>0, "Cost should be positive");
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
        this->jobPtrList = inDevice.jobPtrList;


        /*
         * Pointer bullshittery that should no longer be needed
        for (std::vector<Job *>::const_iterator ptrIt = inDevice.jobPtrList.begin();
             ptrIt != inDevice.jobPtrList.end(); ++ptrIt) {
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

        this->jobPtrList.push_back(&*(ownSystem->jobVect.end() - 1));


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
        outDevice.jobPtrList = inDevice.jobPtrList;
        outDevice._initCheck = &outDevice;

        /*


         if (inDevice.jobPtrList.size()>0) {

            for (std::vector<Job *>::const_iterator ptrIt = inDevice.jobPtrList.begin();
                 ptrIt != inDevice.jobPtrList.end(); ++ptrIt) {
                (*ptrIt)->setOwnDevice(this);
            }
        }
         */
        return *this;
    }




/*
    void Device::updatePointer(Job *inPointer, const Job *prevPointer) {

        for (std::vector<Job *>::iterator ptrIt = this->jobPtrList.begin(); ptrIt != this->jobPtrList.end(); ++ptrIt) {

            if ((*ptrIt) == prevPointer) {
                *ptrIt = inPointer;
            }
        }


    }
    */

    void Device::removeJob(unsigned int jobNr) {

        REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to remove a job from queu");

        for (std::vector<Job *>::iterator ptrIt = this->jobPtrList.begin(); ptrIt != this->jobPtrList.end(); ++ptrIt) {

            if ((*ptrIt)->getJobNr() == jobNr) {
                this->jobPtrList.erase(ptrIt);
                break;
            }
            if (ptrIt == (this->jobPtrList.end() - 1)) {
                std::cerr << "jobNr not found, mysterious" << std::endl;
                return;
            }

        }

    }

    int Device::getTotalPages() {

        REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to get total pages");

        int pages = 0;

        if (this->jobPtrList.size() > 0) {
            for (std::vector<Job *>::iterator jobIt = jobPtrList.begin(); jobIt != jobPtrList.end(); jobIt++) {
                pages += (*jobIt)->getPageCount();
            }
            return pages;
        } else {
            return 0;
        }


    }

    void Device::addJob(Job *jobIn) {

        REQUIRE(this->properlyInitialized(), "Device was not properly initialized when attempting to add a job");


        this->jobPtrList.push_back(jobIn);

        ENSURE(*jobPtrList.back() == *jobIn, "Job was not correctly added");

    }



} // System