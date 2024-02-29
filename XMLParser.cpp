//
// Created by tim on 29/02/24.
//

#include "XMLParser.h"

XMLParser::XMLParser(const char *filename) {

    TiXmlDocument InputDoc;

    if (InputDoc.LoadFile(filename)) {
        std::cerr << InputDoc.ErrorDesc() << std::endl;
    }


    TiXmlElement *System = InputDoc.FirstChildElement();
    REQUIRE(System != NULL, "There is no system in xml");

    TiXmlElement *Device = System->FirstChildElement();
    for (TiXmlElement *elem = Device->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement()) {

        std::string elemname = elem->Value();
        std::cout << elemname << std::endl;

        std::cout << elem->FirstChild()->ToText()->Value() << std::endl;


        std::cout << "test" << std::endl;
    }

    for (TiXmlElement *Job = Device->NextSiblingElement(); Job != NULL;
         Job = Job->NextSiblingElement()) {

        for (TiXmlElement *JobElem = Job->FirstChildElement(); JobElem != NULL;
             JobElem = JobElem->NextSiblingElement()) {

            std::string name = JobElem->Value();

            if (name == "jobNumber") {


                unsigned int JobNr = std::stoi(JobElem->FirstChild()->ToText()->Value());
                std::cout << "jobnr = " << JobNr << std::endl;
            }
        }


    }
}
