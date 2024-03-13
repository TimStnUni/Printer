//
// Created by tim on 29/02/24.
//

#ifndef PROJSOFTENG_PRINTER_H
#define PROJSOFTENG_PRINTER_H


#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <fstream>
#include <queue>


#include "DesignByContract.h"
#include "tinystr.h"
#include "tinyxml.h"

//TestComment2

namespace Printer {


    class Device {
    public:
        Device();

        /**
         * \brief Usual constructor for a printer device
         * @param name : Name of the printer as a string
         * @param emissions : Emissions of the printer in g/page
         * @param speed : Speed of the printer in p/minute
         * ENSURE(this->properlyInitialized(), "Device is not properly initialized");
         */
        Device(std::string name, int emissions, int speed);


        /**
         * \brief A getter function for the printer name
         * @return : returns the name of the printer
         * REQUIRE(this->properlyInitialized(), "Device not initialized when calling getName()");
         */
        std::string getName();


        /**
         * \brief a getter function for the printer emissions
         * @return emissions of the printer in g/page
         * REQUIRE(this->properlyInitialized(), "Device not initialized when calling getEmissions()");
         */
        int getEmissions();

        /**
         * \brief a getter function for the printer speed
         * @return speed in pages/minute
         * REQUIRE(this->properlyInitialized(), "Device not initialized when calling getSpeed()")
         */
        int getSpeed();


    protected:
        std::string name;
        int emissions, speed;

        Device *_initCheck;


        bool properlyInitialized();


    };


    class Job {

    public:
        Job();

        /**
         * \brief Usual contstructor for a printing job
         * @param userName_in Username of the owner of the printing job
         * @param pageCount_in How many pages need to be printed
         * @param jobNr_in JobNr for the job
         *
         * ENSURE(this->properlyInitialized(), "Job wasn't properly initialized")
         */
        Job(std::string userName_in, int pageCount_in, int jobNr_in);


        /**
         * \brief Getter function for the jobnr
         * @return unsigned integer version of the jobnr, these should theoretically always be positive, though this is not required by the standard
         * REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getJobNr()")
         */
        unsigned int getJobNr();

        /**
         * \brief Getter function for the Username
         * @return username as a string
         * REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getUserName()")
         */
        std::string getUserName();

        /**
         * \brief Getter function for the PageCount
         * @return
         * REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getPageCount()")
         */
        int getPageCount();


    private:
        int jobNr, pageCount;
        std::string userName;
        Job *_initCheck;

        bool properlyInitialized();


    };


    class XMLParser {

    public:



        //Todo: Write tests


        XMLParser();


        /**
         *
         * \brief Constructor for parser
         * @param filename : Name of file to parse as a const char *
         *
         * ENSURE(properlyInitialized(), "Parser not properly initialized");

         */
        XMLParser(const char *filename);

        /**
         * \brief Constructor for the parser which takes a string. Currently not implemented
         * @param filename : Name of file to parse as a string
         */
        XMLParser(std::string filename);

        ~XMLParser();


        /**
         * \brief Getter function for the name. Not properly defined at the moment. XMLParser need to go through a thorough redesign
         * @return
         * REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getName()")
         */
        std::string getName();


        //REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getSpeed()");
        int getSpeed();


        //REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getEmissions()");
        int getEmissions();

        //REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getDeviceList()");
        std::vector<Device> getDeviceList();


        //REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getJobList()")
        std::deque<Job> getJobList();

        //REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getJobNrList()")
        std::unordered_set<unsigned int> getJobNrList();


        //REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getNrOfJobs()")
        int getNrOfJobs();

    private:

        XMLParser *_initCheck;

        bool properlyInitialized();


        void parse();

        TiXmlDocument InputDoc;


        //these should probably all be removed
        std::string name;
        int speed, emissions;

        int jobNr, pageCount;
        std::string userName;


        //new datamembers
        std::vector<Device> deviceList;
        std::deque<Job> jobList;
        std::unordered_set<unsigned int> jobNrList;


    };


    /**
     * \brief Printer class. This contains some devices (can technically be 0, for now no functionality changes) and some jobs
     */

    class Printer {


    public:


        /**
         * \brief Constructor for a printer (not a printer device).
         * ENSURE(this->properlyInitialized(), "Printer was not properly initialized");
         */
        Printer();

        //todo: make references again
        //As of now these do not work with references, but this should be possible to be remedied

        //Todo make a version of this function that takes a single device and pushes it back into the devicelist

        //Todo: when getDevice and getJobs is more properly implemented, these should ensure they are correctly set.
        /**
         * \brief Function to add a printer device to a printer container
         * @param device_in a vector of devices to be added.
         * REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling addDevices()")
         * ENSURE(getDevice(device_in.getName) == device_in, "adding devices went wrong
         * //The above ensure is not yet implemented, and wouldn't work with the current implementation anyways
         */
        void addDevices(std::vector<Device> device_in);

        /**
         * \brief Function to add some jobs to a printer
         * @param jobs Double ended queue of jobs.
         * @param jobnrs Unordered set of jobnrs. This is in the process of being reimplemented
         * REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling addJobs()")
         */
        void addJobs(std::deque<Job> jobs, std::unordered_set<unsigned int> jobnrs);
        //Todo: Change unordered set into something better (probably just a vector here)
        //Also potential to have this be a map of jobnrs to jobs. This keeps the duplication checking intact


        //this is technically not very general
        /**
         * \brief Getter function for a printer device. Currently poorly implemented to always return the first device stored in the printer
         * @return first device stored in the printer
         * REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling getPrinter()")
         */
        Device getPrinter();

        /**
         * \brief Getter for all jobs
         * @return
         */
        std::deque<Job> getJobList();

        /**
         * \brief Getter for all jobnrs.
         * @return
         */
        std::unordered_set<unsigned int> getJobNrList();


    private:

        Printer *_initCheck;

        bool properlyInitialized();

        //Todo: Change to map
        std::vector<Device> deviceList;

        //todo: Change to map
        std::deque<Job> jobList;
        std::unordered_set<unsigned int> jobNrSet;

    };

    class PrinterSystem {

    public:
        //Should simply always be running, no input in constructor.

        /**
         * \brief Constructor for the printer system. Does not take any inputs, simply sets the system running.
         */
        PrinterSystem();


        //todo: i believe this should be a private or protected function. I think that means we need to declare the tests as a friend?
        bool properlyInitialized();


        /**
         * \brief Reads an XML file and adds all devices/jobs inside to the printer system
         * @param filename
         */
        void readXML(const char *filename);




        //Todo: This needs to be generalized to any output type. Should probably be given some sort of stream reference to dump its outputs into
        /**
         * \brief Function that prints all know information about the printing system to a file
         * @param filename Filename of the output file
         *REQUIRE(properlyInitialized(), "the printer system was not properly initialized")
         */
        void getInfo(std::string filename);


        //Todo: Change the way jobnrs are stored
        /**
         * \brief Function that executes a print job. Implementation currently seems to have some issues because of the storage solution for jobnrs
         * @param jobnr JobNr of the job to be executed
         */
        void doPrintJob(unsigned int jobnr);

    private:
        std::vector<Printer> printerList;

        PrinterSystem *_initcheck;

        //Naming is the same as for printer.
        //Potentially this should be replaced by a map that maps a jobnr to a pointer to the job, or at least to some
        //way of identifying which job it belongs to. Right now its own index in the unordered set is also the index of the
        //printer list. This won't work, since there can be multiple jobs within a Printer container.
        //This should probably be a map of jobNr's that map to either indices or pointers to printers in the printerList.
        //Within those there can be a set that simply uses its own index to point to the correct job.
        std::unordered_set<unsigned int> jobNrSet;


        /*If replaced by the following it could probably be implemented as something like
        this->addprinter(printer){
            printerlist.push_back(printer)
            int printerindex = printerlist.size() - 1;

            std::unordered_set<unsigned int> printernrs = printer.getPrinterNrs();

            for (printernrs.size, iterate over printernrs (should probably be done with iterators, but those are a bit finnicky)){
                jobNrMap.add({printernrs.at(i), printerindex});
                }
        }


        this way if later some jobnr needs to be fetched it's a case of

         getJob(jobnr){
            printerlist.at(jobNrMap.at(jobnr)).getJob(jobnr){
                //Some relevant code to be implemented in the printer class, don't know what they would want



        */
        std::unordered_map<unsigned int, unsigned int> jobNrMap;

    };

} // Printer

#endif //PROJSOFTENG_PRINTER_H
