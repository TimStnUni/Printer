//
// Created by tim on 18/04/24.
//

#ifndef PROJSOFTENG_XMLPARSER_H
#define PROJSOFTENG_XMLPARSER_H

#include "Logger.h"
#include "DesignByContract.h"
#include "tinystr.h"
#include "tinyxml.h"
#include <string>
#include <iostream>
#include "Device.h"
#include "Job.h"
#include <map>
#include <set>
#include <unordered_set>
#include <vector>
#include <vector>
#include <fstream>


namespace System {

    class PrinterSystem;

    class XMLParser {

    public:


        /**
         * \brief default constructor
         * ENSURE(this->properlyInitialized(), "Parser wasn't properly initialized");
         */
        XMLParser();



        /**
         *
         * \brief Constructor for parser
         * @param filename : Name of file to parse as a const char *
         * REQUIRE(filename != nullptr, "Inputfile should be properly given")
         * ENSURE(properlyInitialized(), "Parser not properly initialized");
         */
        XMLParser(const char *filename, std::ostream & errorStream);

        /**
         * \brief Additional way to read an XML File through the parser, never used
         * @param filename
         * @return
         * REQUIRE(this->properlyInitialized(), "Parser wasn't properly initialized when calling addInputFile");
         * REQUIRE(filename != nullptr, "File should be properly given");
         */

        bool addInputFile(const char * filename);

        ~XMLParser();


        /**
         * \brief Getter function that returns all Devices read in from xml
         * @return vector of devices
         * REQUIRE(this->properlyInitialized, "XMLParser wasn't properly initialized)
         */
        std::vector<Device*>* getDeviceList();


        /**
         * \brief Getter function for getting a joblist
         * @return vector of jobs
         * REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getJobList()")
         */


        std::vector<Job*>* getJobList();



        /**
         * \brief Getter function for the set of jobnr's. Might still be usable?
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

        bool isConsistent() const;



    private:

        XMLParser *_initCheck;
        bool parseSuccessful = true;

        bool properlyInitialized() const;


        /**
         * \brief Function that parses the XML file supplied to the constructor.
         * @param errorstream Stream to store errors
         * REQUIRE(System != nullptr, "There is no system in xml");
         * REQUIRE(properlyInitialized(), "XMLParser was not properly initialized when attempting to call parse");
         */

        bool parse(std::ostream &errorstream);

        TiXmlDocument InputDoc;




        //new datamembers
        std::vector<Device*> deviceList;
        std::vector<Job*> jobList;

        std::set<unsigned int> jobNrSet;


    };


} // System

#endif //PROJSOFTENG_XMLPARSER_H
