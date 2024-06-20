//
// Created by stand on 28/04/2024.
//

#ifndef PROJSOFTENG_SCHEDULER_H
#define PROJSOFTENG_SCHEDULER_H

#include "Job.h"
#include "Device.h"
#include <unordered_set>


namespace System {

    class PrinterSystem;

    class Scheduler {

        //friend class PrinterSystem;

    public:
        /**
         * Default constructor for scheduler
         * ENSURE(properlyInitialized(), "Scheduler not properly initialized")
         */
        Scheduler();

        /**
         * \brief Constructor for scheduler
         * @param PrintSystem
         * ENSURE(this->properlyInitialized(), "Scheduler was not properly initialized")
         */
        Scheduler(PrinterSystem * PrintSystem);


        /**
         * \brief Function that assigns a job for the ownerSystem to a printer
         * @param jobIn: pointer to job that needs to be scheduled
         * @param devVect: pointer to container of all devices
         * REQUIRE(properlyInitialized(), "Scheduler not properly initialized when attempting to schedule a job")
         * ENSURE(jobIn->getOwnDevice() != nullptr, "Job was not assigned to a device, even though the error path was not triggered");
         */

        //todo: maybe split devVect into a setter function?
        void schedule(Job * jobIn, std::unordered_set<Device *> * devVect);


        /**
         * \brief Setter function for the system for which this scheduler works
         * @param PrintSystem
         * REQUIRE(properlyInitialized(), "Scheduler was not properly initialized when attempting to set its ownsystem")
         * REQUIRE(ownSystem == PrintSystem, "Assignment of ownsystem for scheduler failed")
         */

        void setSystem(PrinterSystem * PrintSystem);




    private:

        //PrinterSystem * ownSystem = nullptr;
        Scheduler * _initcheck;
        bool properlyInitialized();


    };

} // System

#endif //PROJSOFTENG_SCHEDULER_H
