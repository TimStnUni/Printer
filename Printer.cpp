//
// Created by tim on 29/02/24.
//

#include "Printer.h"

namespace Printer {
    Device::Device(std::string name_in, int emissions_in, int speed_in) {

        REQUIRE(emissions_in > 0, "Emissions should be positive");
        REQUIRE(speed_in > 0, "Speed should be positive");

        name = name_in;
        emissions = emissions_in;
        speed = speed_in;


        //TOdo : implement properlyinitialized
        //ENSURE(this->properlyInitialized, "inti");
    }





    ///////////////////////////////////////////////////////////
    //
    //
    //////////////////////////////////////////////////////////

    Job::Job(std::string userName_in, int pageCount_in, int jobNr_in) {

        userName = userName_in;
        pageCount = pageCount_in;
        jobNr = jobNr_in;

    }

    Printer::Printer() {

    }

    void Printer::addDevices(std::vector<Device> &device_in) {

        //deviceList.insert(deviceList.end(), device_in.begin(), device_in.end());

        deviceList = device_in;
    }

    void Printer::addJobs(std::vector<Job> &jobs, std::unordered_set<unsigned int> &jobnrs) {

        /*
        jobList.insert(jobList.end(), jobs.begin(), jobs.end());

        for (std::unordered_set<unsigned int>::iterator it = jobnrs.begin(); it != jobnrs.end(); it++) {

            jobNrSet.insert(*it);

        }
         */

        jobList = jobs;
        jobNrSet = jobnrs;


    }

    PrinterSystem::PrinterSystem() {

    }

    void PrinterSystem::readXML(const char * filename) {

        XMLParser tempXML(filename);

        Printer tempPrtr;

        tempPrtr.addDevices(tempXML.getDeviceList());

        std::unordered_set<unsigned int> jobnrs;
        tempPrtr.addJobs(tempXML.getJobList(), jobnrs);



        printerList.push_back(tempPrtr);

        int printerIndex = printerList.size()-1;

        for (std::unordered_set<unsigned int>::iterator it = jobnrs.begin(); it != jobnrs.end(); it++) {

            jobNrMap.insert({*it, printerIndex});

        }




        }
} // Printer