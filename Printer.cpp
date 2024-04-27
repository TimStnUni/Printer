//
// Created by tim on 29/02/24.
//

#include "Printer.h"

namespace System {


    /////////////////////////////////////////////////////////////////
    //
    //
    //XMLPARSER
    //
    ////////////////////////////////////////////////////////////////////








    ///////////////////////////////////////////////////////////
    //
    //
    //////////////////////////////////////////////////////////



    Printer::Printer() {

        _initCheck = this;

        ENSURE(this->properlyInitialized(), "Printer was not properly initialized");

    }

    void Printer::addDevices(std::vector<Device> device_in) {

        REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling addDevices()");


        deviceList.insert(deviceList.end(), device_in.begin(), device_in.end());


        for (int i = 0; i < device_in.size(); i++) {
            Device tempDev = device_in.at(i);
            ENSURE(this->getDevice(deviceList.size() - device_in.size() + i) == tempDev, "Device was added correctly");
        }
    }

    void Printer::addJobs(std::vector<Job> &jobs, std::map<unsigned int, unsigned int> &jobnrs,
                          std::set<unsigned int> &jobNrSet) {
        REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling addJobs()");


        jobList.insert(jobList.end(), jobs.begin(), jobs.end());

        for (std::set<unsigned int>::iterator it = jobNrSet.begin(); it != jobNrSet.end(); it++) {

            jobNrSet.insert(*it);

        }

        for (std::map<unsigned int, unsigned int>::iterator mapIt = jobnrs.begin(); mapIt != jobnrs.end(); mapIt++) {

            jobNrMap.insert({mapIt->first, mapIt->second});

        }



        //Todo: Add a ensure here in the style of addDevices


    }

    Device Printer::getDevice(int index) {
        REQUIRE(this->properlyInitialized(), "printer wasn't properly initialized when calling getDevice()");
        REQUIRE(index >= 0 && index < this->deviceList.size(), "Index should be within bounds");

        return deviceList.at(index);
    }

//    Device Printer::getDeviceList() {
//        REQUIRE(this->properlyInitialized(), "printer wasn't properly initialized when calling getDevice()");
//        return deviceList;
//    }
//TODO: use this function to iterate and search for the right devicetype for a jobtype
    std::vector<Device> Printer::getDeviceList() {
        REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling getDeviceList()");
        return deviceList;
    }

    std::vector<Job> Printer::getJobList() {
        REQUIRE(this->properlyInitialized(), "printer wasn't properly initialized when calling getDevice()");
        return jobList;
    }

    std::map<unsigned int, unsigned int> Printer::getJobNrMap() {
        REQUIRE(this->properlyInitialized(), "printer wasn't properly initialized when calling getDevice()");
        return jobNrMap;
    }

    bool Printer::properlyInitialized() {
        return (this == _initCheck);
    }


    Printer::Printer(const Printer &inPrinter) {

        jobList = inPrinter.jobList;
        jobNrMap = inPrinter.jobNrMap;

        deviceList = inPrinter.deviceList;


        _initCheck = this;


    }

    std::set<unsigned int> Printer::getJobNrSet() {
        return jobNrSet;
    }

    unsigned int Printer::getJobIndex(unsigned int &jobNr) {
        return jobNrMap.at(jobNr);
    }

    void Printer::removeJob(unsigned int jobNr) {

        jobList.erase(jobList.begin() + jobNrMap.at(jobNr));


        unsigned int jobindex = jobNrMap.at(jobNr);
        jobNrMap.erase(jobNr);


        for (std::map<unsigned int, unsigned int>::iterator jobMapIt = jobNrMap.begin();
             jobMapIt != jobNrMap.end(); jobMapIt++) {
            if (jobMapIt->second > jobindex) {
                jobMapIt->second = jobMapIt->second - 1;
            }

        }


    }

}