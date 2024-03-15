//
// Created by tim on 29/02/24.
//

#ifndef PROJSOFTENG_PRINTER_H
#define PROJSOFTENG_PRINTER_H


#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <fstream>
#include <queue>


#include "DesignByContract.h"
#include "tinystr.h"
#include "tinyxml.h"

//Todo: the requires don't work with the copy constructor. Ask Kasper

namespace System {
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
         * \brief Copy Constructor that should fix the _initCheck to this, but somehow that doesn't seem to happen
         * @param inDevice device to be copied
         */
        Device(const Device &inDevice);


        /**
         * \brief Setter function for the name of a device
         * @param inName string name of device
         * REQUIRE(!inName.emtpy(), "name should not be empty")
         * ENSURE(getNameDev() == inName, "name was not correctly set")
         */
        void setNameDev(std::string &inName);

        /**
         * \brief A getter function for the printer name
         * @return : returns the name of the printer
         * REQUIRE(this->properlyInitialized(), "Device not initialized when calling getNameDev()");
         */
        std::string getNameDev() const;


        /**
         * \brief A setter function for the printer emissions
         * @param emissions_in
         * REQUIRE(emissions_in>0, "emissions should be positive")
         * ENSURE(this->getEmissions == emissions_in, "Emissions not correctly set")
         */

        void setEmissions(int &emissions_in);

        /**
         * \brief a getter function for the printer emissions
         * @return emissions of the printer in g/page
         * REQUIRE(this->properlyInitialized(), "Device not initialized when calling getEmissions()");
         */
        int getEmissions() const;


        /**
         * \brief A setter function for the printer speed
         * @param speed_in
         * REQUIRE(speed_in > 0, "Speed should be positive")
         * ENSURE(this->getSpeed() == speed_in, "Speed wasn't correctly set")
         */

        void setSpeed(int &speed_in);

        /**
         * \brief a getter function for the printer speed
         * @return speed in pages/minute
         * REQUIRE(this->properlyInitialized(), "Device not initialized when calling getSpeed()")
         */
        int getSpeed() const;


        bool operator == (const Device &d){
            if (name == d.name && emissions == d.emissions && speed == d.speed){
                return true;
            }
            return false;
        }

    protected:
        std::string name;
        int emissions, speed;

        Device *_initCheck;


        bool properlyInitialized() const;


    };


    class Job {

    public:
        Job();

        Job(const Job &inJob);

        /**
         * \brief Usual constructor for a printing job
         * @param userName_in Username of the owner of the printing job
         * @param pageCount_in How many pages need to be printed
         * @param jobNr_in JobNr for the job
         *
         *REQUIRE(!userName_in.empty(), "Username shouldn't be empty");
         *REQUIRE(pageCount_in>0, "Pagecount should be positive");
         *
         * ENSURE(this->properlyInitialized(), "Job wasn't properly initialized")
         */
        Job(std::string userName_in, int pageCount_in, int jobNr_in);


        /**
         * \brief Getter function for the jobnr
         * @return unsigned integer version of the jobnr, these should theoretically always be positive, though this is not required by the standard
         * REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getJobNr()")
         */
        unsigned int getJobNr()const;

        /**
         * \brief Getter function for the Username
         * @return username as a string
         * REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getUserName()")
         */
        std::string getUserName()const;

        /**
         * \brief Getter function for the PageCount
         * @return
         * REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getPageCount()")
         */
        int getPageCount()const;


        /**
         * \brief Setter function for jobNr
         * @param jobNr
         * REQUIRE(jobNr_in>0, "jobnr should be positive")
         * ENSURE(this->getJobNr() == jobNr_in, "Jobnr not correctly set")
         */

        void setJobNr(int jobNr);

        /**
         * \brief Setter function for the pagecount
         * @param pageCount
         * REQUIRE(pageCount_in > 0, "Pagecount should be positive")
         * ENSURE(this->getPageCount() == pageCount_in, "Pagecount not correctly set")
         */

        void setPageCount(int pageCount);


        /**
         * \brief Setter function for username
         * @param userName
         * REQUIRE(!userName_in.empty(), "Username should not be empty")
         * ENSURE(this->getUserName() == userName_in, "Username not correctly set")
         */
        void setUserName(const std::string &userName);

    private:
        int jobNr, pageCount;
        std::string userName;
        Job *_initCheck;

        bool properlyInitialized() const;


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

        void addInputFile(const char * filename);

        ~XMLParser();


        /**
         * \brief Getter function that returns all Devices read in from xml
         * @return
         * REQUIRE(this->properlyInitialized, "XMLParser wasn't properly initialized)
         */
        std::vector<Device> getDeviceList();


        /**
         * \brief Getter function for getting a joblist
         * @return double ended queue of jobs
         * REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getJobList()")
         */


        std::deque<Job> getJobList();


        /**
         * \brief Getter function for the map of jobNr's to jobs
         * @return
         * //REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getJobNrList()")
         */

        std::map<unsigned int, unsigned int> getJobNrMap();

        /**
         * \brief Getter function for the set of jobnr's
         * @return
         * REQUIRE(this->properlyInitialized(), "parser not properly initialized when calling getJobNrSet()");
         */

        std::set<unsigned int> getJobNrSet();


        /**
         * \brief Function that returns the amount of jobs. Currently unused
         * @return
         */
        //REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getNrOfJobs()")
        int getNrOfJobs();
        bool isParseSuccessful() const;

    private:

        XMLParser *_initCheck;
        bool parseSuccessful = true;

        bool properlyInitialized();


        /**
         * \brief Function that parses the XML file supplied to the constructor.
         */

        bool parse();

        TiXmlDocument InputDoc;




        //new datamembers
        std::vector<Device> deviceList;
        std::deque<Job> jobList;
        std::map<unsigned int, unsigned int> jobNrMap;
        std::set<unsigned int> jobNrSet;


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

        Printer(const Printer &inPrinter);

        //todo: make references again
        //As of now these do not work with references, but this should be possible to be remedied

        //Todo make a version of this function that takes a single device and pushes it back into the devicelist

        //Todo: when getDevice and getJobs is more properly implemented, these should ensure they are correctly set.
        /**
         * \brief Function to add a printer device to a printer container
         * @param device_in a vector of devices to be added.
         * REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling addDevices()")
         *
         * //The above ensure is not yet implemented, and wouldn't work with the current implementation anyways
         */
        void addDevices(std::vector<Device> device_in);

        /**
         * \brief Function to add some jobs to a printer
         * @param jobs Double ended queue of jobs.
         * @param jobnrs Unordered set of jobnrs. This is in the process of being reimplemented
         * REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling addJobs()")
         */
        void
        addJobs(std::deque<Job> &jobs, std::map<unsigned int, unsigned int> &jobnrs, std::set<unsigned int> &jobnrSet);



        //this is technically not very general
        /**
         * \brief Getter function for a printer device. Currently poorly implemented to always return the first device stored in the printer
         * @return first device stored in the printer
         * REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling getDevice()")
         */
        Device getDevice(int index);

        /**
         * \brief Getter for all jobs
         * @return
         */
        std::deque<Job> getJobList();

        /**
         * \brief Getter for all jobnrs. This should be deprecated
         * @return
         */
        std::map<unsigned int, unsigned int> getJobNrMap();

        std::set<unsigned int> getJobNrSet();

        unsigned int getJobIndex(unsigned int &jobNr);


        void removeJob(unsigned int jobNr);

    private:

        Printer *_initCheck;

        bool properlyInitialized();

        std::vector<Device> deviceList;



        //The deque idea was cute but ultimately uneccesary since we never actually loop over it.
        //The entire idea of using sets and maps for duplicate checking is neat, but ultimately should probably not be
        //outside of this. Do I really want to reengineer all the functions? No. Should I? probably.

        //The deque is nice for the looping over all jobs since then it's a simple pop-front or pop-back operation
        //but now it's simply a more complicated joblist.
        std::deque<Job> jobList;
        std::map<unsigned int, unsigned int> jobNrMap;
        std::set<unsigned int> jobNrSet;

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
        bool readXML(const char *filename);




        //Todo: add a way to specify where the output should be stored. Look at later tictactoe versions
        /**
         * \brief Function that prints all know information about the printing system to a file
         * @param filename Filename of the output file
         *REQUIRE(properlyInitialized(), "the printer system was not properly initialized")
         */
        void getInfo(std::string filename);




        //Todo: add a way to specify where the output should be stored. Look at later tictactoe versions
        /**
         * \brief Function that executes a print job. Implementation currently seems to have some issues because of the storage solution for jobnrs
         * @param jobnr JobNr of the job to be executed
         */
        void doPrintJob(unsigned int jobnr);

        /**
         * \brief Loops over all jobs and prints that they are finished.
         */

        void printAll();


    private:
        std::vector<Printer> printerList;

        PrinterSystem *_initcheck;

        //Naming is the same as for printer.
        //Potentially this should be replaced by a map that maps a jobnr to a pointer to the job, or at least to some
        //way of identifying which job it belongs to. Right now its own index in the unordered set is also the index of the
        //printer list. This won't work, since there can be multiple jobs within a Printer container.
        //This should probably be a map of jobNr's that map to either indices or pointers to printers in the printerList.
        //Within those there can be a set that simply uses its own index to point to the correct job.
        std::set<unsigned int> jobNrSet;


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
        std::map<unsigned int, unsigned int> jobNrMap;

    };

} // Printer

#endif //PROJSOFTENG_PRINTER_H
