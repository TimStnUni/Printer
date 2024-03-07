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

    //File should be closed. Not entirely sure what they mean by this? If this was using some ifstream
    //there would be a .close() function, but that doesn't seem to exist for TiXMLDocuments

    ENSURE(properlyInitialized(), "Parser not properly initialized");

    //Potentially add some check here for properlyparsed? could also split parse from the constructor and always
    //have the printer class call .parse() on it's parser.

    //Todo: Step 3 of the use case still needs to be checked. I believe this needs to be done in the printer class.
    //The issue is mostly whether they mean that the jobnr's should be unique per xml file we read in,
    //or whether they should be unique over the entire printer system. If it's the entire printer system, it cannot
    //be checked here. If it's within a single xml file, it's fine.

    //I assume it will need to be systemwide, and in spec 2.0 they'll ask us to be able to get a specific printjob by
    //its corresponding jobNr.
}


void XMLParser::parse() {

    TiXmlElement *System = InputDoc.FirstChildElement();

    //Probably not a require, probably just if

    REQUIRE(System != NULL, "There is no system in xml");

    //Should make device and job here, then use setters to assingn them their values



    for (TiXmlElement *Level1Elem = System->FirstChildElement(); Level1Elem != NULL;
         Level1Elem = Level1Elem->NextSiblingElement()) {

        std::string type = Level1Elem->Value();


        //Todo: Replace all straight assignments with a setter function?
        //Can technically move checks into those functions? is this better?

        if (type == "DEVICE") {
            for (TiXmlElement *elem = Level1Elem->FirstChildElement(); elem != NULL;
                 elem = elem->NextSiblingElement()) {

                std::string elemname = elem->Value();


                if (elemname == "name") {
                    std::string name_t = elem->FirstChild()->ToText()->Value();
                    if (name_t.empty()) {
                        std::cout << "Name should not be empty" << std::endl;
                        continue;

                    } else {
                        name = name_t;
                    }


                } else if (elemname == "emissions") {

                    if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                        emissions = std::stoi(elem->FirstChild()->ToText()->Value());
                    } else {
                        std::cout << "Emissions should be positive" << std::endl;
                        continue;


                    }


                } else if (elemname == "speed") {
                    if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                        speed = std::stoi(elem->FirstChild()->ToText()->Value());
                    } else {
                        std::cout << "speed should be positive" << std::endl;
                        continue;
                    }

                }
                else {
                    std::cout << "Element name " << elemname << " is either empty or an unexpected element name" << std::endl;
                    continue;
                }
            }
        } else if (type == "JOB") {

            for (TiXmlElement *elem = Level1Elem->FirstChildElement(); elem != NULL;
                 elem = elem->NextSiblingElement()) {

                std::string elemname = elem->Value();


                if (elemname == "userName") {
                    std::string userName_t = elem->FirstChild()->ToText()->Value();
                    if (userName_t.empty()){
                        std::cout << "username should not be empty" << std::endl;
                        continue;
                    }else{
                        userName = userName_t;
                    }

                } else if (elemname == "pageCount") {
                    if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0){
                        pageCount = std::stoi(elem->FirstChild()->ToText()->Value());
                    }else{
                        std::cout << "pagecount should be a positive integer" << std::endl;
                        continue;
                    }


                } else if (elemname == "jobNumber") {
                    if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                        jobNr = std::stoi(elem->FirstChild()->ToText()->Value());
                    }else{
                        //Not actually sure this needs to be a positive integer
                        std::cout << "jobnumber should be a positive integer" << std::endl;
                    }
                }
                else{
                    std::cout << "Element name " << elemname << "is either empty or an unexpected element name" << std::endl;
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

