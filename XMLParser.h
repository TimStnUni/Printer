//
// Created by tim on 29/02/24.
//

#ifndef TESTSCONTRACTS_XMLPARSER_H
#define TESTSCONTRACTS_XMLPARSER_H

#include <string>
#include <iostream>


#include "tinyxml.h"
#include "DesignByContract.h"
#include "Printer.h"
//Since this is including printer, and printer is including this, should they just be in the same file?


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

    XMLParser(const char * filename);

    std::string getName();
    int getSpeed();
    int getEmissions();

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
    std::vector<Printer::Printer> printerList;
    std::vector<Printer::Job> jobList;
    std::unordered_set<unsigned int> jobNrList;


};


#endif //TESTSCONTRACTS_XMLPARSER_H
