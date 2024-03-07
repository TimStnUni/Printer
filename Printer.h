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
        Device(std::string name, int emissions, int speed);

        std::string getName();
        int getEmissions();
        int getSpeed();


    protected:
        std::string name;
        int emissions, speed;


    };


    class Job {

    public:
        Job();
        Job(std::string userName_in, int pageCount_in, int jobNr_in);

        unsigned int getJobNr();
        std::string getUserName();
        int getPageCount();


    private:
        int jobNr, pageCount;
        std::string userName;
    };


    class XMLParser {

    public:

        /**
         *
         * \brief Constructor for parser
         * @param filename : Name of file to parse
         *
         * ENSURE(properlyInitialized(), "Parser not properly initialized");

         */

        //Todo: Write tests


        XMLParser();
        XMLParser(const char * filename);
        XMLParser(std::string filename);
        ~XMLParser();


        std::string getName();
        int getSpeed();
        int getEmissions();

        std::vector<Device> getDeviceList();
        std::deque<Job> getJobList();
        std::unordered_set<unsigned int> getJobNrList();

        int getNrOfJobs();

    private:

        XMLParser * _initCheck;
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




    class Printer {


    public:



        Printer();

        //todo: make references again
        void addDevices(std::vector<Device> device_in);
        void addJobs(std::deque<Job> jobs, std::unordered_set<unsigned int> jobnrs);


        //this is technically not very general
        Device getPrinter();
        std::deque<Job> getJobList();
        std::unordered_set<unsigned int> getJobNrList();





    private:
        std::vector<Device> deviceList;
        std::deque<Job> jobList;
        std::unordered_set<unsigned int> jobNrSet;

    };

    class PrinterSystem {

    public:
        //Should simply always be running, no input in constructor.
        PrinterSystem();

        bool properlyInitialized();

        void readXML(const char * filename);

        //        REQUIRE(properlyInitialized(), "the printer system was not properly initialized");
        void getInfo(std::string filename);


        void doPrintJob(unsigned int jobnr);

    private:
        std::vector<Printer> printerList;

        PrinterSystem * _initcheck;

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
