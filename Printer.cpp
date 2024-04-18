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

    void Printer::addJobs(std::deque<Job> &jobs, std::map<unsigned int, unsigned int> &jobnrs,
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

    std::deque<Job> Printer::getJobList() {
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

    PrinterSystem::PrinterSystem() {


        _initcheck = this;


    }

    bool PrinterSystem::readXML(const char *filename) {
        XMLParser tempXML(filename);

        //if parse is not successful return false
        if (!tempXML.isParseSuccessful()) {
            return false;
        }
        Printer tempPrtr;

        tempPrtr.addDevices(tempXML.getDeviceList());

        std::map<unsigned int, unsigned int> jobnrs = tempXML.getJobNrMap();
        std::deque<Job> tempJobList = tempXML.getJobList();
        std::set<unsigned int> tempJobSet = tempXML.getJobNrSet();
        tempPrtr.addJobs(tempJobList, jobnrs, tempJobSet);


        printerList.push_back(tempPrtr);

        int printerIndex = printerList.size() - 1;


        std::set<unsigned int>::iterator it;


        for (it = tempJobSet.begin(); it != tempJobSet.end(); ++it) {


            if (jobNrSet.find(*it) == jobNrSet.end()) {

                jobNrMap.insert({*it, printerIndex});
                jobNrSet.insert(*it);

            } else {


                //todo : Expand on this error
                std::cout << "JobNr is not unique" << std::endl;
            }

        }
        return true;

    }

    void PrinterSystem::getInfo(std::string filename) {

        REQUIRE(properlyInitialized(), "the printer system was not properly initialized");


        std::ofstream outfile;
        outfile.open(filename);
        if (!outfile.is_open()) {
            std::cout << "file could not be opened" << std::endl;
        }


        for (std::vector<Printer>::iterator printIt = printerList.begin(); printIt != printerList.end(); ++printIt) {


            Device currentPrinter = printIt->getDevice(0);


            outfile << currentPrinter.getNameDev() << " (CO2: " << currentPrinter.getEmissions() << "g/page; speed "
                    << currentPrinter.getSpeed() << "p/minute):\n";

            std::deque<Job> currentJobs = printIt->getJobList();

            for (std::deque<Job>::iterator jobIt = currentJobs.begin(); jobIt != currentJobs.end(); ++jobIt) {

                if (jobIt == currentJobs.begin()) {

                    outfile << "    * Current: \n";
                } else {
                    outfile << "    * Queue: \n";
                }

                outfile << "        [#" << jobIt->getJobNr() << "|" << jobIt->getUserName() << "|"
                        << jobIt->getPageCount()
                        << "]\n";

            }


            outfile << std::endl;

        }


        outfile.close();

    }

    bool PrinterSystem::properlyInitialized() {
        return (this == _initcheck);
    }

    void PrinterSystem::doPrintJob(unsigned int jobnr, std::ostream &writeStream) {

        int printerindex = jobNrMap.at(jobnr);

        Printer Currentprinter = printerList.at(printerindex);

        Device currentDevice = Currentprinter.getDevice(0);

        std::set<unsigned int> currentJobNrList = Currentprinter.getJobNrSet();


        unsigned int jobnrindex = Currentprinter.getJobIndex(jobnr);

        Job currentJob = Currentprinter.getJobList().at(jobnrindex);


        int pages = currentJob.getPageCount();

        while (pages > 0) {
            pages--;
        }

        writeStream << "Printer \"" << currentDevice.getNameDev() << "\" finished job:\n";
        writeStream << "  Number: " << jobnr << "\n";
        writeStream << "  Submitted by \"" << currentJob.getUserName() << "\"\n";
        writeStream << "  " << currentJob.getPageCount() << " pages\n";

        writeStream << std::endl;
        printerList.at(printerindex).removeJob(jobnr);

        // Remove the job number from the jobNrSet and jobNrMap
        jobNrSet.erase(jobnr);
        jobNrMap.erase(jobnr);
    }

    void PrinterSystem::printAll(std::ostream &writeStream) {

        for (std::set<unsigned int>::iterator jobNrIt = jobNrSet.begin(); jobNrIt != jobNrSet.end(); jobNrIt++) {

            this->doPrintJob(*jobNrIt, writeStream);
        }

    }
} // Printer