//
// Created by stand on 28/04/2024.
//

#ifndef PROJSOFTENG_SCHEDULER_H
#define PROJSOFTENG_SCHEDULER_H

#include "Job.h"
#include "Device.h"
#include <list>
#include "Logger.h"
#include <ostream>


namespace System {

    class PrinterSystem;

    class Scheduler {


    public:
        /**
         * Default constructor for scheduler
         * ENSURE(properlyInitialized(), "Scheduler not properly initialized")
         */
        Scheduler();




        /**
         * \brief Function that assigns a job for the ownerSystem to a printer
         * @param jobIn: pointer to job that needs to be scheduled
         * @param devVect: pointer to container of all devices
         * REQUIRE(properlyInitialized(), "Scheduler not properly initialized when attempting to schedule a job")
         * REQUIRE(jobIn != nullptr && devVect != nullptr, "Inputs shouldn't be nullptrs")
         * ENSURE(jobIn->getOwnDevice() != nullptr, "Job was not assigned to a device, even though the error path was not triggered");
         */


        int schedule(Job * jobIn, std::list<Device *> * devVect, std::ostream & errorStream);



    private:


        Scheduler * _initcheck;
        bool properlyInitialized();
        Logger logger;

    };

} // System

#endif //PROJSOFTENG_SCHEDULER_H
