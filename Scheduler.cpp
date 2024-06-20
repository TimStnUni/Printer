//
// Created by stand on 28/04/2024.
//

#include "Scheduler.h"
#include "PrinterSystem.h"
#include <climits>
#include <algorithm>
#include <map>

namespace System {
    Scheduler::Scheduler(PrinterSystem *PrintSystem) {

        _initcheck = this;


        //Test whether this is still required
        //this->ownSystem = PrintSystem;



        ENSURE(this->properlyInitialized(), "Scheduler was not properly initialized");


    }

    bool Scheduler::properlyInitialized() {
        return (this == _initcheck);
    }

    bool Scheduler::schedule(Job *jobIn, std::unordered_set<Device *> *devVect) {


        //Todo: CO2 limits mogen exceeded zijn in inlezen, het is pas hier dat we daar rekening mee moeten houden en for some
        // reason houden we dan wel die printers in het systeem maar smijten we jobs weg die we niet kunnen printen?


        //todo: check opsplitsen in type en limit, want die moeten blijkbaar aparte errors geven

        REQUIRE(properlyInitialized(), "Scheduler not properly initialized when attempting to schedule a job");


        std::string jobType = jobIn->getType();







        std::vector<Device *> posDevs;

        for (std::unordered_set<Device *>::iterator devIt = devVect->begin(); devIt != devVect->end(); devIt++) {

            if ((*devIt)->getType() == jobType && (*devIt)->belowLimit()) {
                posDevs.push_back(*devIt);


            }
        }
        if (posDevs.empty()) {

            logger.printNoDevice(std::cerr, jobIn->getJobNr());

            return false;
        }


        std::map<int, Device *> devVals;
        for (std::vector<Device *>::iterator posIt = posDevs.begin(); posIt != posDevs.end(); posIt++){

            int val = (*posIt)->getTotalPages();
            val *= (*posIt)->getEmissions();

            devVals.insert({val, *posIt});
        }



        (devVals.begin()->second)->addJob(jobIn);
        jobIn->setOwnDevice(*posDevs.begin());




        ENSURE(jobIn->getOwnDevice() != nullptr,
               "Job was not assigned to a device, even though the error path was not triggered");

        return true;
    }

    Scheduler::Scheduler() {

        _initcheck = this;

        ENSURE(properlyInitialized(), "Scheduler was not properly initialized");

    }


    /*
    void Scheduler::setSystem(PrinterSystem *PrintSystem) {

        REQUIRE(properlyInitialized(), "Scheduler was not properly initialized when attempting to set its ownsystem");


        ownSystem = PrintSystem;

        REQUIRE(ownSystem == PrintSystem, "Assignment of ownsystem for scheduler failed");

    }
     */
} // System