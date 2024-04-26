//
// Created by stand on 26/04/2024.
//

#ifndef PROJSOFTENG_PRINTERSYSTEM_H
#define PROJSOFTENG_PRINTERSYSTEM_H

#include "Printer.h"
#include "XMLParser.h"

namespace System {


    class PrinterSystem {
        friend class Device;

    public:
        //Should simply always be running, no input in constructor.

        /**
         * \brief Constructor for the printer system. Does not take any inputs, simply sets the system running.
         */
        PrinterSystem();


        /**
         * \brief Reads an XML file and adds all devices/jobs inside to the printer system
         * @param filename
         */
        bool readXML(const char *filename);






        //TODO: change this over to a stream to either print to terminal or to file.
        /**
         * \brief Function that prints all known information about the printing system to a file
         * @param filename Filename of the output file
         *REQUIRE(properlyInitialized(), "the printer system was not properly initialized")
         */
        void getInfo(std::string filename);


        /**
         * \brief Function that executes a print job. Implementation currently seems to have some issues because of the storage solution for jobnrs
         * @param jobnr JobNr of the job to be executed
         * @param writeStream Stream where the output is stored
         */
        void doPrintJob(unsigned int jobnr, std::ostream &writeStream);

        /**
         * \brief Loops over all jobs and prints that they are finished.
         * @param writeStream Stream where the output will be stored
         */

        void printAll(std::ostream &writeStream);


        /**
         * Adder function for a single job
         * @param inJob
         */
        void addJob(Job &inJob);

        /**
         * adder function for a single device
         * @param inDevice
         */
        void addDevice(Device inDevice);

        const Job *getMRJob();
        void takeParseInput(Device & inDev, std::deque<Job>& inJobs);


    private:



        bool properlyInitialized();

        std::vector<Printer> printerList;

        PrinterSystem *_initcheck;

        std::set<unsigned int> jobNrSet;


        std::map<unsigned int, unsigned int> jobNrMap;

        std::vector<Job> jobVect;
        std::vector<Device> deviceVect;


    };


} // System

#endif //PROJSOFTENG_PRINTERSYSTEM_H
