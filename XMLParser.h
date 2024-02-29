//
// Created by tim on 29/02/24.
//

#ifndef TESTSCONTRACTS_XMLPARSER_H
#define TESTSCONTRACTS_XMLPARSER_H

#include <string>
#include <iostream>


#include "tinyxml.h"
#include "DesignByContract.h"


class XMLParser {

public:

    /**
     *
     * \brief Constructor for parser
     * @param filename : Name of file to parse
     *
     * ENSURE(properlyInitialized(), "Parser not properly initialized");

     */

    XMLParser(const char * filename);

    std::string getName();
    int getSpeed();
    int getEmissions();

private:

    XMLParser * _initCheck;
    bool properlyInitialized();


    void parse();

    TiXmlDocument InputDoc;
    std::string name;
    int speed, emissions;

    int jobNr, pageCount;
    std::string userName;



};


#endif //TESTSCONTRACTS_XMLPARSER_H
