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

void System::InfoPrinter::printAscii(std::ostream &outfile) {

    REQUIRE(properlyInitialized(), "InfoPrinter was not properly initialized when attempting to print ASCII");


    outfile << "# === [System Status] === #\n\n" << std::endl;


    outfile << "   --=== Printers: ===--\n" << std::endl;


    for (std::vector<Device*>::iterator printIt = ownSystem->getDeviceVector()->begin(); printIt != ownSystem->getDeviceVector()->end(); ++printIt) {

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





    }


    outfile << "      --=== Jobs ===--\n" << std::endl;

    for (std::vector<Job*>::iterator jobIt = ownSystem->getJobVector()->begin();
         jobIt != ownSystem->getJobVector()->end(); ++jobIt) {

        std::string jobType;



        if ((*jobIt)->getType() == "bw") {
            jobType = "Black-and-white job";
        } else if ((*jobIt)->getType() == "color") {
            jobType = "Colour job";
        } else if ((*jobIt)->getType() == "scan") {
            jobType = "Scanning job";
        }

        if (jobIt == ownSystem->getJobVector()->begin()) {

            outfile << "    * Current:\n";
        }


        float totalcost = (float)(*jobIt)->getPageCount() * (*jobIt)->getOwnDevice()->getCost();
        float totalCO2 = (float)(*jobIt)->getPageCount() * (float)(*jobIt)->getOwnDevice()->getEmissions();

        //Todo: Add device when device and job have been overhauled. Also add total co2 and cost when that's gettable
        outfile << "        [Job #" << (*jobIt)->getJobNr() << "]\n"
                << "            * Owner: " << (*jobIt)->getUserName() << "\n"
                << "            * Total Pages: " << (*jobIt)->getPageCount() << "\n"
                << "            * Pages Printed: " << (*jobIt)->getPrintedPages() << "\n"
                << "            * Type: " << jobType << "\n"
                << "            * Device: " << (*jobIt)->getOwnDevice()->getNameDev() << "\n"
                << "            * Total CO2: " << totalCO2 << "\n"
                << "            * Total cost: " << totalcost << "\n";

        if (jobIt == ownSystem->getJobVector()->begin()) {

            outfile << "    * Queue:\n";
        }
    }


    outfile << std::endl;

}
    void System::InfoPrinter::setSystem(System::PrinterSystem *inSystem) {

        REQUIRE(properlyInitialized(), "InfoPrinter not properly initialized when attempting to set system");

        this->ownSystem = inSystem;

        ENSURE(ownSystem == inSystem, "System was not correclty assigned");

    }
