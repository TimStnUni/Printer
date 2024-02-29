//
// Created by tim on 29/02/24.
//

#include "XMLParser.h"

XMLParser::XMLParser(const char *filename) {


    if (InputDoc.LoadFile(filename)) {
        std::cerr << InputDoc.ErrorDesc() << std::endl;
    }

    _initCheck = this;
    this->parse();

    ENSURE(properlyInitialized(), "Parser not properly initialized");
}


void XMLParser::parse() {

    TiXmlElement *System = InputDoc.FirstChildElement();
    REQUIRE(System != NULL, "There is no system in xml");


    for (TiXmlElement *Level1Elem = System->FirstChildElement(); Level1Elem != NULL;
         Level1Elem = Level1Elem->NextSiblingElement()) {

        std::string type = Level1Elem->Value();

        if (type == "DEVICE") {
            for (TiXmlElement *elem = Level1Elem->FirstChildElement(); elem != NULL;
                 elem = elem->NextSiblingElement()) {

                std::string elemname = elem->Value();


                if (elemname == "name") {
                    name = elem->FirstChild()->ToText()->Value();

                        if (name.empty()){
                            std::cerr << "name should not be emtpy" << std::endl;
                        }

                } else if (elemname == "emissions") {
                    emissions = std::stoi(elem->FirstChild()->ToText()->Value());
                    ENSURE(emissions > 0, "Emissions should be positive");

                } else if (elemname == "speed") {
                    speed = std::stoi(elem->FirstChild()->ToText()->Value());
                    ENSURE(speed > 0, "Speed should be positive");
                }
            }
        } else if (type == "JOB") {

            for (TiXmlElement *elem = Level1Elem->FirstChildElement(); elem != NULL;
                 elem = elem->NextSiblingElement()) {

                std::string elemname = elem->Value();


                if (elemname == "userName") {
                    userName = elem->FirstChild()->ToText()->Value();
                } else if (elemname == "pageCount") {
                    pageCount = std::stoi(elem->FirstChild()->ToText()->Value());
                } else if (elemname == "jobNumber") {
                    jobNr = std::stoi(elem->FirstChild()->ToText()->Value());
                }
            }

        } else {

            std::cerr << "Element should be either a printer or a Job, is a " << type << std::endl;


            continue;

        }


    }


}

std::string XMLParser::getName() {
    return name;
}

int XMLParser::getSpeed() {
    return speed;
}

int XMLParser::getEmissions() {
    return emissions;
}

bool XMLParser::properlyInitialized() {
    return (this == _initCheck);
}

