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

    //Probably not a require, probably just if

    REQUIRE(System != NULL, "There is no system in xml");

    //Should make device and job here, then use setters to assign them their values



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
                    int emissions_t = std::stoi(elem->FirstChild()->ToText()->Value());
                    if (emissions_t <= 0){
                        std::cout << "Emissions should be positive" << std::endl;
                        continue;
                    }else {
                        emissions = emissions_t;
                    }

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

