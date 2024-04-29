//
// Created by stand on 28/04/2024.
//

#include "Scheduler.h"
#include "PrinterSystem.h"
#include <climits>

namespace System {
    Scheduler::Scheduler(PrinterSystem *PrintSystem) {

        _initcheck = this;

        this->ownSystem = PrintSystem;



        ENSURE(this->properlyInitialized(), "Scheduler was not properly initialized");


    }

    bool Scheduler::properlyInitialized() {
        return (this == _initcheck);
    }

    void Scheduler::schedule(Job * jobIn) {



        REQUIRE(properlyInitialized(), "Scheduler not properly initialized when attempting to schedule a job");

        //This should be reworked to jobnr's;


        std::string jobType = jobIn->getType();

        std::vector<Device>::iterator stopIt = ownSystem->deviceVect.end();

        int pageQueue = INT_MAX;


        for (std::vector<Device>::iterator devIt = ownSystem->deviceVect.begin(); devIt!=ownSystem->deviceVect.end(); devIt++){

            if (devIt->getTotalPages() < pageQueue && devIt->getType() == jobType){
                pageQueue = devIt->getTotalPages();
                stopIt = devIt;
            }
        }
        if (stopIt == ownSystem->deviceVect.end()){
            std::cerr << "No suitable device found for job " << jobIn->getJobNr() << std::endl;
            return;
        }else{
            stopIt->addJob(jobIn);
            jobIn->setOwnDevice(&(*stopIt));

            //Job is now scheduled and should be removed from jobnrset
            ownSystem->jobNrSet.erase(jobIn->getJobNr());


        }





    }

    Scheduler::Scheduler() {

        _initcheck = this;

        ENSURE(properlyInitialized(), "Scheduler was not properly initialized");

    }

    void Scheduler::setSystem(PrinterSystem *PrintSystem) {

        REQUIRE(properlyInitialized(), "Scheduler was not properly initialized when attempting to set its ownsystem");


        ownSystem = PrintSystem;

        REQUIRE(ownSystem == PrintSystem, "Assignment of ownsystem for scheduler failed");

    }
} // System