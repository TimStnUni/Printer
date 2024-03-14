//
// Created by tim on 29/02/24.
//

#ifndef PROJSOFTENG_PRINTER_H
#define PROJSOFTENG_PRINTER_H


#include <iostream>
#include <string>
#include <vector>
#include <set>

#include "DesignByContract.h"
#include "tinystr.h"
#include "tinyxml.h"


namespace Printer {


    class Device {
    public:
        Device(std::string  name, int  emissions, int  speed);

        std::string getName();
        int getEmissions();
        int getSpeed();


    protected:
        std::string name;
        int emissions, speed;


    };


    class Job {

    public:
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
    };

    class Printer {


    public:
        Printer();




    private:
        std::vector<Device> deviceList;
        std::vector<Job> jobList;
        std::set<unsigned int> jobNrSet;

    };

} // Printer

#endif //PROJSOFTENG_PRINTER_H
