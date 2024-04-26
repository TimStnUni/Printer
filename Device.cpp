//
// Created by tim on 18/04/24.
//

#include "Device.h"
#include "Job.h"

namespace System {



    Device::Device(std::string name_in, int emissions_in, int speed_in, std::string type_in, float cost_in) {
        //REQUIRE(emissions_in > 0, "Emissions should be positive");
        //REQUIRE(speed_in > 0, "Speed should be positive");

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

//TODO: something is wrong here, but I don't know how to fix it
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


        ENSURE(this->properlyInitialized(), "Device not properly initialized in copy constructor");


    }

    void Device::setNameDev(std::string &inName) {


        REQUIRE(!inName.empty(), "name shouldn't be empty");
        this->name = inName;

        ENSURE(this->getNameDev() == inName, "Name not correctly set");

    }

    void Device::setEmissions(int &emissions_in) {

        REQUIRE(emissions_in > 0, "Emissions should be positive");
        this->emissions = emissions_in;
        ENSURE(this->getEmissions() == emissions_in, "Emissions not correctly set");

    }

    void Device::setSpeed(int &speed_in) {

        REQUIRE(speed_in > 0, "Speed should be positive");

        this->speed = speed_in;

        ENSURE(this->getSpeed() == speed_in, "Speed not correctly set");

    }

    void Device::setType(std::string &type_in) {
        REQUIRE(!type_in.empty(), "Type shouldn't be empty");
        this->type = type_in;
        ENSURE(this->getType() == type_in, "Type not correctly set");
    }

    void Device::setCost(float &cost_in) {
        REQUIRE(cost_in >= 0, "Cost should be positive");
        this->cost = cost_in;
        ENSURE(this->getCost() == cost_in, "Cost not correctly set");
    }

} // System