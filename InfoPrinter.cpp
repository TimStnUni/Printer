//
// Created by stand on 28/04/2024.
//

#include "InfoPrinter.h"
#include "PrinterSystem.h"


System::InfoPrinter::InfoPrinter() {


    _initcheck = this;

    ENSURE(this->properlyInitialized(), "Infoprinter was not properly initialized");

}

bool System::InfoPrinter::properlyInitialized() {
    return (_initcheck == this);
}

void System::InfoPrinter::setSystem(System::PrinterSystem *inSystem) {

    REQUIRE(properlyInitialized(), "InfoPrinter not properly initialized when attempting to set system");

    this->ownSystem = inSystem;

    ENSURE(ownSystem == inSystem, "System was not correclty assigned");

}


void System::InfoPrinter::printAscii(std::ostream &outfile) {

    REQUIRE(properlyInitialized(), "InfoPrinter was not properly initialized when attempting to print ASCII");


    outfile << "# === [System Status] === #\n\n" << std::endl;


    outfile << "   --=== Printers: ===--\n" << std::endl;


    for (std::list<Device *>::iterator printIt = ownSystem->getDeviceVector()->begin();
         printIt != ownSystem->getDeviceVector()->end(); ++printIt) {

        //TODO: layout aanpassen?


        std::string printType;

        if ((*printIt)->getType() == "bw") {
            printType = "Black-and-white printer";
        } else if ((*printIt)->getType() == "color") {
            printType = "Colour printer";
        } else if ((*printIt)->getType() == "scan") {
            printType = "Scanner";
        }


        outfile << (*printIt)->getNameDev() << std::endl;
        outfile << "    * CO2: " << (*printIt)->getEmissions() << " g/page" << "\n"
                << "    * " << printType << "\n"
                << "    * " << (*printIt)->getSpeed() << " pages/minute\n"
                << "    * " << (*printIt)->getCost() << " cents/page\n";


        outfile << "      -= Jobs =-\n" << std::endl;

        for (std::deque<Job *>::iterator jobIt = (*printIt)->getJobs()->begin();
             jobIt != (*printIt)->getJobs()->end(); ++jobIt) {

            std::string jobType;


            if ((*jobIt)->getType() == "bw") {
                jobType = "Black-and-white job";
            } else if ((*jobIt)->getType() == "color") {
                jobType = "Colour job";
            } else if ((*jobIt)->getType() == "scan") {
                jobType = "Scanning job";
            }

            if (jobIt == (*printIt)->getJobs()->begin()) {

                outfile << "    * Current:\n";
            }


            float totalcost = (float) (*jobIt)->getPageCount() * (*jobIt)->getOwnDevice()->getCost();
            float totalCO2 = (float) (*jobIt)->getPageCount() * (float) (*jobIt)->getOwnDevice()->getEmissions();

            outfile << "        [Job #" << (*jobIt)->getJobNr() << "]\n"
                    << "            * Owner: " << (*jobIt)->getUserName() << "\n"
                    << "            * Total Pages: " << (*jobIt)->getPageCount() << "\n"
                    << "            * Pages Printed: " << (*jobIt)->getPrintedPages() << "\n"
                    << "            * Type: " << jobType << "\n"
                    << "            * Device: " << (*jobIt)->getOwnDevice()->getNameDev() << "\n"
                    << "            * Total CO2: " << totalCO2 << "\n"
                    << "            * Total cost: " << totalcost << "\n";

            if (jobIt == (*printIt)->getJobs()->begin()) {

                outfile << "    * Queue:\n";
            }
        }
    }


    outfile << std::endl;

}


void System::InfoPrinter::printAdvancedAscii(std::ostream &outfile) {
    REQUIRE(properlyInitialized(), "infoprinter wasn't properly initialized");


    for (std::list<Device *>::iterator devsIt = ownSystem->getDeviceVector()->begin();
         devsIt != ownSystem->getDeviceVector()->end(); devsIt++) {

        outfile << (*devsIt)->getNameDev() << std::endl;

        std::deque<Job *> * jobs = (*devsIt)->getJobs();

        outfile << "    ";
        for (std::deque<Job*>::iterator jobsIt = jobs->begin(); jobsIt != jobs->end(); jobsIt++){

            if (jobsIt == jobs->begin()){

                outfile << (*jobsIt)->getUserName() << ":" << "[" << (*jobsIt)->getRemainingPages() << "/" << (*jobsIt)->getPageCount() << "] | ";
            }else{

                outfile << (*jobsIt)->getUserName() << ":"  << "[" << (*jobsIt)->getPageCount() << "] || ";
            }


        }

        outfile << std::endl;

    }


}
