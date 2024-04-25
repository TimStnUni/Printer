//
// Created by tim on 18/04/24.
//

#include "XMLParser.h"

namespace System {


    XMLParser::XMLParser(const char *filename) {
//        std::cout <<  InputDoc.LoadFile(filename) << std::endl;
        //Todo: check whether inputdoc isn't empty
        if (!InputDoc.LoadFile(filename)) {
            std::cerr << InputDoc.ErrorDesc() << std::endl;
        }


        _initCheck = this;
        std::ofstream outFile; // Create an output file stream
        std::string f = filename;
        std::string outputFileName = f + ".txt";
        const char *outputFileNameChar = outputFileName.c_str();
        outFile.open(outputFileNameChar); // Open the file


        parseSuccessful = this->parse(outFile);


        ENSURE(properlyInitialized(), "Parser not properly initialized");
    }


    bool XMLParser::parse(std::ostream &errorstream) {

        TiXmlElement *System = InputDoc.FirstChildElement();


        REQUIRE(System != nullptr, "There is no system in xml");

        for (TiXmlElement *Level1Elem = System->FirstChildElement(); Level1Elem != NULL;
             Level1Elem = Level1Elem->NextSiblingElement()) {

            std::string type_sys = Level1Elem->Value();


            if (type_sys == "DEVICE") {
                bool readingCorrect = true;
                std::string name;
                int emissions, speed;
                std::string type;

                for (TiXmlElement *elem = Level1Elem->FirstChildElement(); elem != NULL;
                     elem = elem->NextSiblingElement()) {

                    std::string elemname = elem->Value();
                    std::string test;


                    if (elem->FirstChild() == nullptr) {
                        readingCorrect = false;

                        errorstream << elemname << "should not be empty" << std::endl;
                        return readingCorrect;
                    } else {

                        if (elemname == "name") {


                            std::string name_t = elem->FirstChild()->ToText()->Value();


                            if (name_t.empty()) {
                                errorstream << "Name should not be empty" << std::endl;
                                readingCorrect = false;
                                return readingCorrect;

                            } else {
                                name = name_t;
                                //std::cout << "name = " << name << std::endl;
                            }


                        } else if (elemname == "emissions") {

                            if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                                emissions = std::stoi(elem->FirstChild()->ToText()->Value());

                            } else {
                                errorstream << "Emissions should be positive" << std::endl;
                                readingCorrect = false;
                                return readingCorrect;


                            }
//TODO: check if correct, do we need to add cost?
                        }else if (elemname == "type") {


                            std::string type_d = elem->FirstChild()->ToText()->Value();


                            if (type_d.empty()) {
                                errorstream << "Type should not be empty" << std::endl;
                                readingCorrect = false;
                                return readingCorrect;

                            } else {
                                type = type_d;
                                //std::cout << "type = " << type << std::endl;
                            }

                        } else if (elemname == "speed") {
                            if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                                speed = std::stoi(elem->FirstChild()->ToText()->Value());
                            } else {
                                errorstream << "speed should be positive" << std::endl;
                                readingCorrect = false;
                                return readingCorrect;
                            }

                        } else {
                            std::cout << "Element name " << elemname << " is either empty or an unexpected element name"
                                      << std::endl;
                            readingCorrect = false;
                            continue;
                        }

                    }
                }
                if (readingCorrect) {
                    Device tempPrinter = Device(name, emissions, speed, type);
                    deviceList.push_back(tempPrinter);
                }


            } else if (type_sys == "JOB") {
                std::string userName;
                int pageCount, jobNr;
                std::string type;
                bool readingCorrectly = true;

                for (TiXmlElement *elem = Level1Elem->FirstChildElement(); elem != NULL;
                     elem = elem->NextSiblingElement()) {


                    std::string elemname = elem->Value();


                    if (elemname == "userName") {
                        auto t = elem->FirstChild();
                        if (t == NULL) {
                            errorstream << "username should not be empty" << std::endl;
                            readingCorrectly = false;
                            return readingCorrectly;
                        } else {
                            std::string userName_t = elem->FirstChild()->ToText()->Value();
                            userName = userName_t;

                        }

                    } else if (elemname == "pageCount") {
                        if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                            pageCount = std::stoi(elem->FirstChild()->ToText()->Value());
                        } else {
                            errorstream << "pagecount should be a positive integer" << std::endl;
                            readingCorrectly = false;
                            return readingCorrectly;
                        }


                    } else if (elemname == "jobNumber") {
                        if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                            jobNr = std::stoi(elem->FirstChild()->ToText()->Value());
                        } else {
                            //Not actually sure this needs to be a positive integer
                            errorstream << "jobnumber should be a positive integer" << std::endl;
                            readingCorrectly = false;
                            return readingCorrectly;
                        }

//TODO: check if correct
                    }else if (elemname == "type") {


                        std::string type_j = elem->FirstChild()->ToText()->Value();


                        if (type_j.empty()) {
                            errorstream << "Type should not be empty" << std::endl;
                            readingCorrectly = false;
                            return readingCorrectly;

                        } else {
                            type = type_j;
                            //std::cout << "type = " << type << std::endl;
                        }

                    } else {
                        std::cout << "Element name " << elemname << "is either empty or an unexpected element name"
                                  << std::endl;
                        readingCorrectly = false;
                        continue;
                    }
                }

                if (readingCorrectly) {





                    //todo loops twice for some reason, investigate

                    //Implement better duplicate checking off the return value for insert?
                    if (jobNrSet.find(jobNr) == jobNrSet.end()) {
                        //Job is only added to joblist if its jobnr is unique
                        Job tempJob = Job(userName, pageCount, jobNr, type);
                        jobList.push_back(tempJob);
                        jobNrMap.insert({jobNr, jobList.size() - 1});
                        jobNrSet.insert(jobNr);

                    } else {

                        errorstream << "Jobnumber should be unique" << std::endl;
                        return false;
                    }

                }


            } else {

                std::cerr << "Element should be either a printer or a Job, is a " << type_sys << std::endl;


                continue;

            }


        }

        return true;
    }


    bool XMLParser::properlyInitialized() {
        return (this == _initCheck);
    }

    std::vector<Device> XMLParser::getDeviceList() {
        REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getDeviceList()");
        return deviceList;
    }

    std::deque<Job> XMLParser::getJobList() {
        REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getJobList()");
        return jobList;
    }

    std::map<unsigned int, unsigned int> XMLParser::getJobNrMap() {
        REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getJobNrMap()");
        return jobNrMap;
    }

    XMLParser::~XMLParser() {
        InputDoc.Clear();

    }

    XMLParser::XMLParser() {

        _initCheck = this;

        ENSURE(this->properlyInitialized(), "Parser wasn't properly initialized");

    }

    int XMLParser::getNrOfJobs() {
        REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getNrOfJobs()");
        return jobList.size();
    }

    std::set<unsigned int> XMLParser::getJobNrSet() {
        return jobNrSet;
    }

    bool XMLParser::addInputFile(const char *filename) {

        REQUIRE(this->properlyInitialized(), "Parser wasn't properly initialized when calling addInputFile");

        if (InputDoc.LoadFile(filename)) {
            std::cerr << InputDoc.ErrorDesc() << std::endl;
        }
        std::ofstream outFile; // Create an output file stream
        std::string f = filename;
        std::string outputFileName = f + ".txt";
        const char *outputFileNameChar = outputFileName.c_str();
        outFile.open(outputFileNameChar); // Open the file

        parseSuccessful = this->parse(outFile);

        return parseSuccessful;

    }

    bool XMLParser::isParseSuccessful() const {
        return parseSuccessful;
    }

} // System