//
// Created by stand on 26/04/2024.
//

#include "PrinterSystem.h"

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
        Printer tempPrtr;


        tempPrtr.addDevices(tempXML.getDeviceList());

        std::map<unsigned int, unsigned int> jobnrs = tempXML.getJobNrMap();
        std::vector<Job> tempJobList = tempXML.getJobList();
        std::set<unsigned int> tempJobSet = tempXML.getJobNrSet();
        tempPrtr.addJobs(tempJobList, jobnrs, tempJobSet);


        printerList.push_back(tempPrtr);

        int printerIndex = printerList.size() - 1;


        std::set<unsigned int>::iterator it;


        for (it = tempJobSet.begin(); it != tempJobSet.end(); ++it) {


            if (jobNrSet.find(*it) == jobNrSet.end()) {

                //jobNrMap.insert({*it, printerIndex});
                jobNrSet.insert(*it);

            } else {


                //todo : Expand on this error
                std::cout << "JobNr is not unique" << std::endl;
            }

        }

        //std::cout << this->jobVect.at(0).getOwnDevice()->getNameDev() << std::endl;


        return true;

    }

    void PrinterSystem::getInfo(std::ostream & writeStream, std::string outputType) {

        REQUIRE(properlyInitialized(), "the printer system was not properly initialized");


        for (std::set<unsigned int>::reverse_iterator jobnrIt = jobNrSet.rbegin();
             jobnrIt != jobNrSet.rend(); jobnrIt++) {

            for (std::vector<Job>::iterator jobsIt = jobVect.begin(); jobsIt != jobVect.end(); jobsIt++) {

                if (jobsIt->getJobNr() == *jobnrIt) {
                    system_scheduler.schedule(&(*jobsIt));
                }
            }

        }





        InfoPrinter printer;
        printer.setSystem(this);


        if (outputType == "ASCII") {

            printer.printAscii(writeStream);
        }

        else{
            std::cerr << "Unsupported output type, reverting to ASCII" << std::endl;
            printer.printAscii(writeStream);
        }


        /*
        outfile << "# === [System Status] === #\n" << std::endl;


        for (std::vector<Device>::iterator printIt = deviceVect.begin(); printIt != deviceVect.end(); ++printIt) {

            //TODO: layout aanpassen?


            std::string printType;

            if (printIt->getType() == "bw") {
                printType = "Black-and-white printer";
            } else if (printIt->getType() == "color") {
                printType = "Colour printer";
            } else if (printIt->getType() == "scan") {
                printType = "Scanner";
            }


            outfile << printIt->getNameDev() << std::endl;
            outfile << "    * CO2: " << printIt->getEmissions() << " g/page" << "\n"
                    << "    * " << printType << "\n"
                    << "    * " << printIt->getSpeed() << " pages/minute\n"
                    << "    * " << printIt->getCost() << " cents/page \n";





        }
        for (std::vector<Job>::iterator jobIt = this->jobVect.begin();
             jobIt != this->jobVect.end(); ++jobIt) {

            std::string jobType;



            if (jobIt->getType() == "bw") {
                jobType = "Black-and-white job ";
            } else if ((jobIt)->getType() == "color") {
                jobType = "Colour job ";
            } else if ((jobIt)->getType() == "scan") {
                jobType = "Scanning job ";
            }

            if (jobIt == jobVect.begin()) {

                outfile << "    * Current: \n";
            }


            float totalcost = (jobIt)->getPageCount() * jobIt->getOwnDevice()->getCost();
            float totalCO2 = (jobIt)->getPageCount() * jobIt->getOwnDevice()->getEmissions();

            //Todo: Add device when device and job have been overhauled. Also add total co2 and cost when that's gettable
            outfile << "        [Job #" << (jobIt)->getJobNr() << "]\n"
                    << "            * Owner: " << (jobIt)->getUserName() << "\n"
                    << "            * Total Pages: " << (jobIt)->getPageCount() << "\n"
                    << "            * Type: " << jobType << "\n"
                    << "            * Device: " << jobIt->getOwnDevice()->getNameDev() << "\n"
                    << "            * Total CO2: " << totalCO2 << "\n"
                    << "            * Total cost: " << totalcost << "\n";

            if (jobIt == jobVect.begin()) {

                outfile << "    * Queue: \n";
            }
        }


        outfile << std::endl;

        */


    }

    bool PrinterSystem::properlyInitialized() {
        return (this == _initcheck);
    }

    //TODO: create a check to see if the devicetype matches the jobtype and if not
    // go to a different device in the devicelist and search until you find one that matches the type of jobtype
    void PrinterSystem::doPrintJob(unsigned int jobnr, std::ostream &writeStream) {

        std::vector<Job>::iterator jobPoint;
        for (std::vector<Job>::iterator jobIt = this->jobVect.begin(); jobIt != this->jobVect.end(); ++jobIt) {
            if (jobIt->getJobNr() == jobnr) {
                jobPoint = jobIt;
                break;
            }
            if (jobIt == (this->jobVect.end())) {
                std::cerr << "JobNr not found" << std::endl;
                return;
            }
        }


        if (this->jobNrSet.find(jobnr) != jobNrSet.end()){
            //This means the job has not yet been scheduled
            system_scheduler.schedule(&(*jobPoint));
        }

        Device *printPoint = jobPoint->getOwnDevice();


        //This rerouting is already done in scheduler now.

        if (jobPoint->getType() != printPoint->getType()) {

            std::cerr << "types don't match" << std::endl;
            for (std::vector<Device>::iterator devIt = this->deviceVect.begin();
                 devIt != this->deviceVect.end(); devIt++) {

                if (devIt->getType() == jobPoint->getType()) {
                    jobPoint->setOwnDevice(&(*devIt));
                    printPoint = jobPoint->getOwnDevice();
                    std::cerr << "Rerouting to device \"" << printPoint->getNameDev() << "\"" << std::endl;
                    break;
                }
                if (devIt == (this->deviceVect.end() - 1)) {
                    std::cerr << "No viable replacement device found, aborting print job " << jobPoint->getJobNr()
                              << " from user " << jobPoint->getUserName() << std::endl;
                    return;
                }

            }

        }


        int pages = jobPoint->getPageCount();


        while (pages > 0) {
            pages--;
        }


        std::string printType;

        if (jobPoint->getType() == "bw") {
            printType = "black-and-white-printing ";
        } else if (jobPoint->getType() == "color") {
            printType = "color-printing ";
        } else if (jobPoint->getType() == "scan") {
            printType = "scanning ";
        }

        writeStream << "Printer \"" << printPoint->getNameDev() << "\" finished " << printType << "job:\n";
        writeStream << "  Number: " << jobnr << "\n";
        writeStream << "  Submitted by \"" << jobPoint->getUserName() << "\"\n";
        writeStream << "  " << jobPoint->getPageCount() << " pages\n";

        writeStream << std::endl;


        //Increment CO2 emissions




        float newCO2 = (jobPoint->getPageCount()) * (printPoint->getEmissions());

        totalCO2_system += newCO2;

        //std::cout << "total CO2 emissions for now " << totalCO2_system << std::endl;


        // Remove the job number from the jobNrSet and jobNrMap
        //This is now already done in scheduler
        jobNrSet.erase(jobnr);

        //TODO: Figure out why erasing seems to miss.
        //jobVect.erase(jobPoint);
        jobPoint->getOwnDevice()->removeJob(jobnr);


    }

    void PrinterSystem::printAll(std::ostream &writeStream) {
        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to print all jobs");

        for (std::set<unsigned int>::iterator jobNrIt = jobNrSet.begin(); jobNrIt != jobNrSet.end(); jobNrIt++) {


            this->doPrintJob(*jobNrIt, writeStream);
        }


        writeStream << "Total CO2 emitted by jobs until now is " << totalCO2_system << " gram" << std::endl;

    }

    void PrinterSystem::addJob(Job &inJob) {

        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a job");

        this->jobVect.emplace_back(inJob);


        //This should be removable but isn't? Weird
        this->jobVect.back().setOwnDevice(&(*(deviceVect.end() - 1)));

        ENSURE(jobVect.back() == inJob, "Job was not correctly added");

        /*


        std::cout << "these should be the same " << &(*(deviceVect.end()-1)) << " and " << (deviceVect.end()-1)->getInitCheck() << " and " << jobVect.back().getOwnDevice() << std::endl;
        std::cout << "and these should exist " << (deviceVect.end()-1)->getInitCheck()->getNameDev() << std::endl;
        std::cout << "and be equal to " << jobVect.back().getOwnDevice()->getNameDev() << std::endl;
        */
    }

    void PrinterSystem::addDevice(Device inDevice) {

        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a device");

        std::vector<string> devicenames;


        for (std::vector<Device>::iterator devIt = this->deviceVect.begin(); devIt != this->deviceVect.end(); devIt++) {

            devicenames.push_back(devIt->getNameDev());


        }

        this->deviceVect.emplace_back(inDevice);


        ENSURE(deviceVect.back() == inDevice, "Device was not correctly added");
/*
        for (int i = 0; i < devicenames.size(); i++) {

            for (std::vector<Device>::iterator devIt2 = this->deviceVect.begin();
                 devIt2 != this->deviceVect.end(); devIt2++) {
                std::vector<Job *> tempJobVect = jobPtrs.at(i);
                if (devIt2->getNameDev() == devicenames.at(i)) {
                    for (std::vector<Job *>::iterator jobIt = tempJobVect.begin();
                         jobIt != tempJobVect.end(); jobIt++) {
                        (*jobIt)->setOwnDevice(&(*devIt2));
                    }
                }

            }
        }
*/

    }


    /*
    const Job *PrinterSystem::getMRJob() {
        return &*(jobVect.end() - 1);
    }
*/
    void PrinterSystem::takeParseInput(Device &inDev, std::vector<Job> &inJobs) {

        REQUIRE(properlyInitialized(), "System wasn't properly initialized when attempting to add devices and jobs");

        this->addDevice(inDev);


        for (std::vector<Job>::iterator jobIt = inJobs.begin(); jobIt != inJobs.end(); ++jobIt) {


            this->addJob(*jobIt);

            //this->deviceVect.back().addJob(this);

        }


    }
//    void PrinterSystem::printAll(unsigned int jobnr, std::ostream &writeStream) {
//        // Find the job with the given number
//        Job job; // Initialize this with the job that has the given number
//
//        // Iterate over all printers
//        for (std::vector<Printer>::iterator printerIt = printerList.begin(); printerIt != printerList.end(); ++printerIt) {
//            // Iterate over all devices in the current printer
//            for (int i = 0; i < printerIt->getDeviceList().size(); i++) {
//                Device device = printerIt->getDevice(i);
//
//                // Check if the device's type matches the job's type
//                if (device.getType() == job.getType()) {
//                    this->doPrintJob(*printerIt, writeStream)
//                }else{
//
//                }
//            }
//            }
//        }
} // PrinterSsytem



