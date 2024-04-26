//
// Created by stand on 26/04/2024.
//

#include "PrinterSystem.h"

namespace System {

    PrinterSystem::PrinterSystem() {


        _initcheck = this;


    }

    bool PrinterSystem::readXML(const char *filename) {
        XMLParser tempXML(filename, this);

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

        std::cout << this->jobVect.at(0).getOwnDevice()->getNameDev() << std::endl;


        return true;

    }

    void PrinterSystem::getInfo(std::string filename) {

        REQUIRE(properlyInitialized(), "the printer system was not properly initialized");


        std::ofstream outfile;
        outfile.open(filename);
        if (!outfile.is_open()) {
            std::cout << "file could not be opened" << std::endl;
        }

        outfile << "# === [System Status] === #\n" << std::endl;

        for (std::vector<Printer>::iterator printIt = printerList.begin(); printIt != printerList.end(); ++printIt) {

            //TODO: index kunnen veranderen
            // In principe gaat dit moeten loopen over devices (die stored zullen zijn in printersystem, het tussenliggend
            // Niveau printer gaat verwijderd worden. Elke Device zal dan een lijst van pointers naar jobs bevatten
            // Zodat er simpelweg vanuit elk device een lijst van jobs opgebouwd kan worden.
            Device currentPrinter = printIt->getDevice(0);

            std::string printType;

            if (currentPrinter.getType() == "bw") {
                printType = "Black-and-white printer";
            } else if (currentPrinter.getType() == "color") {
                printType = "Colour printer";
            }else if (currentPrinter.getType() == "scanner"){
                printType = "Scanner";
            }

            outfile << currentPrinter.getNameDev() << std::endl;
            outfile << "* CO2: " << currentPrinter.getEmissions() << " g/page" << "\n"
                    << "* " << printType << "\n"
                    << "* "  << currentPrinter.getSpeed() << " pages/minute\n"
                    << "* " << currentPrinter.getCost() << " cents/page \n";

            std::deque<Job> currentJobs = printIt->getJobList();

            for (std::deque<Job>::iterator jobIt = currentJobs.begin(); jobIt != currentJobs.end(); ++jobIt) {

                std::string jobType;

                if (jobIt->getType() == "bw") {
                    jobType = "Black-and-white job";
                } else if (jobIt->getType() == "color") {
                    jobType = "Colour job";
                }else if (jobIt->getType() == "scanner"){
                    jobType = "Scanning job";
                }

                if (jobIt == currentJobs.begin()) {

                    outfile << "    * Current: \n";
                }
                //Todo: Add device when device and job have been overhauled. Also add total co2 and cost when that's gettable
                outfile << "        [Job #" << jobIt->getJobNr() << "]\n"
                        << "            * Owner: " << jobIt->getUserName() << "\n"
                        << "            * Total Pages: " << jobIt->getPageCount() << "\n"
                        << "            * Type: " << jobType << "\n"
                        << "            * Device: " << "jobIt->getOwnDevice()->getNameDev() this gives a segfault bcause of course it does" <<"\n"
                        << "            * Total CO2: \n"
                        << "            * Total cost: \n";

                if (jobIt == currentJobs.begin()) {

                    outfile << "    * Queue: \n";
                }
            }


            outfile << std::endl;

        }


        outfile.close();

    }

    bool PrinterSystem::properlyInitialized() {
        return (this == _initcheck);
    }

    //TODO: create a check to see if the devicetype matches the jobtype and if not
    // go to a different device in the devicelist and search until you find one that matches the type of jobtype
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

    void PrinterSystem::addJob(Job &inJob) {

        this->jobVect.emplace_back(inJob);

        this->jobVect.back().setOwnDevice(&deviceVect.back());


       }

    void PrinterSystem::addDevice(Device inDevice) {
        this->deviceVect.emplace_back(inDevice);

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



