//
// Created by stand on 28/04/2024.
//

#include "Scheduler.h"
#include "PrinterSystem.h"
#include <climits>
#include <algorithm>
#include <map>

namespace System {


    bool Scheduler::properlyInitialized() {
        return (this == _initcheck);
    }

    int Scheduler::schedule(Job *jobIn, std::list<Device *> *devVect, std::ostream &errorStream) {


        REQUIRE(properlyInitialized(), "Scheduler not properly initialized when attempting to schedule a job");
        REQUIRE(jobIn != nullptr && devVect != nullptr, "Inputs shouldn't be nullptrs");


        std::string jobType = jobIn->getType();


        std::vector<Device *> posDevs;

        for (std::list<Device *>::iterator devIt = devVect->begin(); devIt != devVect->end(); devIt++) {

            if ((*devIt)->getType() == jobType) {
                posDevs.push_back(*devIt);


            }
        }
        if (posDevs.empty()) {

            logger.printNoDevice(errorStream, jobIn->getJobNr());

            return 1;
        }


        std::map<int, Device *> devVals;
        for (std::vector<Device *>::iterator posIt = posDevs.begin(); posIt != posDevs.end(); posIt++) {

            if ((*posIt)->isBelowLimit()) {
                int val = (*posIt)->getTotalPages();
                val *= (*posIt)->getEmissions();

                devVals.insert({val, *posIt});
            }
        }


        if (devVals.empty()) {

            logger.printError(errorStream, "No available device was below the CO2 threshold");
            return 2;
        }

        (devVals.begin()->second)->addJob(jobIn);
        jobIn->setOwnDevice(*posDevs.begin());


        ENSURE(jobIn->getOwnDevice() != nullptr,
               "Job was not assigned to a device, even though the error path was not triggered");

        return 0;
    }

    Scheduler::Scheduler() {

        _initcheck = this;

        ENSURE(properlyInitialized(), "Scheduler was not properly initialized");

    }

} // System