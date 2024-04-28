//
// Created by stand on 28/04/2024.
//

#ifndef PROJSOFTENG_SCHEDULER_H
#define PROJSOFTENG_SCHEDULER_H

#include "Job.h"
#include "Device.h"
#


namespace System {

    class PrinterSystem;

    class Scheduler {

        friend class PrinterSystem;

        Scheduler();
        Scheduler(PrinterSystem * PrintSystem);

        void schedule(Job * jobIn);

        void setSystem(PrinterSystem * PrintSystem);

        bool properlyInitialized();


    private:

        PrinterSystem * ownSystem = nullptr;
        Scheduler * _initcheck;


    };

} // System

#endif //PROJSOFTENG_SCHEDULER_H
