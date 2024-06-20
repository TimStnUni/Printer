//
// Created by stand on 28/04/2024.
//

#include "Scheduler.h"
#include "PrinterSystem.h"
#include <climits>

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

    void Scheduler::schedule(Job * jobIn, std::unordered_set<Device *> * devVect) {



        REQUIRE(properlyInitialized(), "Scheduler not properly initialized when attempting to schedule a job");


        std::string jobType = jobIn->getType();



        std::unordered_set<Device*>::iterator stopIt = devVect->end();

        int pageQueue = INT_MAX;


        for (std::unordered_set<Device*>::iterator devIt = devVect->begin(); devIt!=devVect->end(); devIt++){

            if ((*devIt)->getTotalPages() < pageQueue && (*devIt)->getType() == jobType){
                pageQueue = (*devIt)->getTotalPages();
                stopIt = devIt;
            }
        }
        if (stopIt == devVect->end()){
            std::cerr << "No suitable device found for job " << jobIn->getJobNr() << std::endl;
            return;
        }else{
            (*stopIt)->addJob(jobIn);
            jobIn->setOwnDevice((*stopIt));
        }


        ENSURE(jobIn->getOwnDevice() != nullptr, "Job was not assigned to a device, even though the error path was not triggered");



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