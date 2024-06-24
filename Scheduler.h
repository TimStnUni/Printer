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
         * REQUIRE(jobIn != nullptr && devVect != nullptr, "Inputs shouldn't be nullptrs")
         * ENSURE(jobIn->getOwnDevice() != nullptr, "Job was not assigned to a device, even though the error path was not triggered");
         */

        //todo: maybe split devVect into a setter function?
        bool schedule(Job * jobIn, std::list<Device *> * devVect, std::ostream * outstream);


        /**
         * \brief Setter function for the system for which this scheduler works
         * @param PrintSystem
         * REQUIRE(properlyInitialized(), "Scheduler was not properly initialized when attempting to set its ownsystem")
         * REQUIRE(ownSystem == PrintSystem, "Assignment of ownsystem for scheduler failed")
         */

        void setSystem(PrinterSystem * PrintSystem);


        /**
         * \brief function to set the outputstream
         * @param inStream
         * REQUIRE(properlyInitialized(), "scheduler wasn't properly initialized");
         * REQUIRE(inStream != nullptr, "Instream should not be a nullptr");
         * ENSURE(outStream == inStream, "Outstream wasn't properly assigned");
         */

        //void setStream(std::ostream * inStream);


    private:

        //PrinterSystem * ownSystem = nullptr;
        Scheduler * _initcheck;
        bool properlyInitialized();


        //std::ostream * outStream = nullptr;

        Logger logger;

    };

} // System

#endif //PROJSOFTENG_SCHEDULER_H
