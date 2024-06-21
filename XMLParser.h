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

        XMLParser();

        //Todo: Look through all of these requires/ensures

        /**
         *
         * \brief Constructor for parser
         * @param filename : Name of file to parse as a const char *
         * REQUIRE inputfile not empty i guess?
         * ENSURE(properlyInitialized(), "Parser not properly initialized");

         */
        XMLParser(const char *filename);

        /**
         * \brief Additional way to read an XML File through the parser, never used
         * @param filename
         * @return
         */

        bool addInputFile(const char * filename);

        ~XMLParser();


        /**
         * \brief Getter function that returns all Devices read in from xml, shouldn't be used any longer
         * @return
         * REQUIRE(this->properlyInitialized, "XMLParser wasn't properly initialized)
         */
        std::unordered_set<Device*>* getDeviceList();


        /**
         * \brief Getter function for getting a joblist, shouldn't be used any longer
         * @return double ended queue of jobs
         * REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getJobList()")
         */


        std::unordered_set<Job*>* getJobList();



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

        bool properlyInitialized();


        /**
         * \brief Function that parses the XML file supplied to the constructor.
         * @param errorstream Stream to store errors
         * REQUIRE(System != nullptr, "There is no system in xml");
         */

        bool parse(std::ostream &errorstream);

        TiXmlDocument InputDoc;




        //new datamembers
        std::unordered_set<Device*> deviceList;
        std::unordered_set<Job*> jobList;

        std::set<unsigned int> jobNrSet;
        Logger logger;


    };


} // System

#endif //PROJSOFTENG_XMLPARSER_H
