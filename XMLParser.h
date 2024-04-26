//
// Created by tim on 18/04/24.
//

#ifndef PROJSOFTENG_XMLPARSER_H
#define PROJSOFTENG_XMLPARSER_H

#include "DesignByContract.h"
#include "tinystr.h"
#include "tinyxml.h"
#include <string>
#include <iostream>
#include "Device.h"
#include "Job.h"
#include <map>
#include <set>
#include <vector>
#include <deque>
#include <fstream>


namespace System {

    class PrinterSystem;

    class XMLParser {

    public:






        XMLParser();


        /**
         *
         * \brief Constructor for parser
         * @param filename : Name of file to parse as a const char *
         *
         * ENSURE(properlyInitialized(), "Parser not properly initialized");

         */
        XMLParser(const char *filename, PrinterSystem * system);

        /**
         * \brief Additional way to read an XML File through the parser
         * @param filename
         * @return
         */

        bool addInputFile(const char * filename);

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
         * //REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getNrOfJobs()")
         */

        int getNrOfJobs();


        /**
         * \brief Getter function for the state of the XMLparser after attempting to parse the input file
         * @return
         */

        bool isParseSuccessful() const;



    private:

        XMLParser *_initCheck;
        bool parseSuccessful = true;

        bool properlyInitialized();


        /**
         * \brief Function that parses the XML file supplied to the constructor.
         * @param errorstream Stream to store errors
         */

        bool parse(std::ostream &errorstream);

        TiXmlDocument InputDoc;


        PrinterSystem * ownSystem;

        //new datamembers
        std::vector<Device> deviceList;
        std::deque<Job> jobList;
        std::map<unsigned int, unsigned int> jobNrMap;
        std::set<unsigned int> jobNrSet;


    };


} // System

#endif //PROJSOFTENG_XMLPARSER_H
