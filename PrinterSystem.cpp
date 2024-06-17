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


        //Todo: remove this part of the code, it shouldn't be needed anymore

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




        return true;

    }

    void PrinterSystem::getInfo(std::ostream & writeStream, std::string outputType) {

        REQUIRE(properlyInitialized(), "the printer system was not properly initialized");


        for (std::set<unsigned int>::reverse_iterator jobnrIt = jobNrSet.rbegin();
             jobnrIt != jobNrSet.rend(); jobnrIt++) {

            for (std::vector<Job*>::iterator jobsIt = jobVect.begin(); jobsIt != jobVect.end(); jobsIt++) {

                if ((*jobsIt)->getJobNr() == *jobnrIt) {
                    system_scheduler.schedule((*jobsIt));
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




    }

    bool PrinterSystem::properlyInitialized() {
        return (this == _initcheck);
    }

    //TODO: create a check to see if the devicetype matches the jobtype and if not
    // go to a different device in the devicelist and search until you find one that matches the type of jobtype
    void PrinterSystem::doPrintJob(unsigned int jobnr, std::ostream &writeStream, bool eraseBool) {




        std::vector<Job*>::iterator jobPoint;


        for (std::vector<Job*>::iterator jobIt = this->jobVect.begin(); jobIt != this->jobVect.end(); ++jobIt) {
            if ((*jobIt)->getJobNr() == jobnr) {
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
            system_scheduler.schedule((*jobPoint));
        }



        Device *printPoint = (*jobPoint)->getOwnDevice();


        //This rerouting is already done in scheduler now.



        if ((*jobPoint)->getType() != printPoint->getType()) {


            std::cerr << "types don't match" << std::endl;
            for (std::vector<Device*>::iterator devIt = this->deviceVect.begin();
                 devIt != this->deviceVect.end(); devIt++) {

                if ((*devIt)->getType() == (*jobPoint)->getType()) {
                    (*jobPoint)->setOwnDevice((*devIt));
                    printPoint = (*jobPoint)->getOwnDevice();
                    std::cerr << "Rerouting to device \"" << printPoint->getNameDev() << "\"" << std::endl;
                    break;
                }
                if (devIt == (this->deviceVect.end() - 1)) {
                    std::cerr << "No viable replacement device found, aborting print job " << (*jobPoint)->getJobNr()
                              << " from user " << (*jobPoint)->getUserName() << std::endl;
                    return;
                }

            }

        }




        int pages = (*jobPoint)->getPageCount();


        while (pages > 0) {
            pages--;
        }


        std::string printType;

        if ((*jobPoint)->getType() == "bw") {
            printType = "black-and-white-printing ";
        } else if ((*jobPoint)->getType() == "color") {
            printType = "color-printing ";
        } else if ((*jobPoint)->getType() == "scan") {
            printType = "scanning ";
        }

        writeStream << "Printer \"" << printPoint->getNameDev() << "\" finished " << printType << "job:\n";
        writeStream << "  Number: " << jobnr << "\n";
        writeStream << "  Submitted by \"" << (*jobPoint)->getUserName() << "\"\n";
        writeStream << "  " << (*jobPoint)->getPageCount() << " pages\n";




        float newCO2 = ((*jobPoint)->getPageCount()) * (printPoint->getEmissions());

        writeStream << "  Job CO2 emissions: " << newCO2 << " gram\n";
        writeStream << std::endl;

        //Increment CO2 emissions
        totalCO2_system += newCO2;

        //std::cout << "total CO2 emissions for now " << totalCO2_system << std::endl;



        if (eraseBool) {

            // Remove the job number from the jobNrSet and jobNrMap
            //This is now already done in scheduler
            jobNrSet.erase(jobnr);

            //TODO: Figure out why erasing seems to miss.
            //jobVect.erase(jobPoint);
            (*jobPoint)->getOwnDevice()->removeJob(jobnr);
        }


    }

    void PrinterSystem::printAll(std::ostream &writeStream) {
        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to print all jobs");





        for (std::set<unsigned int>::reverse_iterator jobNrIt = jobNrSet.rbegin(); jobNrIt != jobNrSet.rend(); jobNrIt++) {


            //Erasing jobnr's is having issues
            this->doPrintJob(*jobNrIt, writeStream, false);

        }


        writeStream << "Total CO2 emitted by jobs until now is " << totalCO2_system << " gram" << std::endl;

    }

    void PrinterSystem::addJob(Job *inJob) {

        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a job");

        this->jobVect.emplace_back(inJob);


        //This should be removable but isn't? Weird
        //this->jobVect.back().setOwnDevice(&(*(deviceVect.end() - 1)));

        ENSURE(jobVect.back() == inJob, "Job was not correctly added");


    }

    void PrinterSystem::addDevice(Device *inDevice) {

        REQUIRE(properlyInitialized(), "System was not properly initialized when attempting to add a device");
        //REQUIRE(inDevice != nullptr, "input device should not be a nullptr");

        this->deviceVect.emplace_back(inDevice);


        ENSURE(deviceVect.back() == inDevice, "Device was not correctly added");


    }


    /*
    const Job *PrinterSystem::getMRJob() {
        return &*(jobVect.end() - 1);
    }
*/
    void PrinterSystem::takeParseInput(Device *inDev, std::vector<Job*> &inJobs) {

        REQUIRE(properlyInitialized(), "System wasn't properly initialized when attempting to add devices and jobs");

        this->addDevice(inDev);


        for (std::vector<Job*>::iterator jobIt = inJobs.begin(); jobIt != inJobs.end(); ++jobIt) {


            this->addJob(*jobIt);

            //this->deviceVect.back().addJob(this);

        }


    }

    PrinterSystem::~PrinterSystem() {

        for (auto dev : this->deviceVect){

            delete dev;
        }
        for (auto job : this->jobVect){
            delete job;
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



