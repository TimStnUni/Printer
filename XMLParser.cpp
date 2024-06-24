//
// Created by tim on 18/04/24.
//

#include "XMLParser.h"
#include "PrinterSystem.h"

namespace System {


    XMLParser::XMLParser(const char *filename, std::ostream & outFile) {

        REQUIRE(filename != nullptr, "Inputfile should be properly given");

        _initCheck = this;

        /*
        std::ofstream outFile; // Create an output file stream
        std::string f = filename;
        std::string outputFileName = f + ".txt";
        const char *outputFileNameChar = outputFileName.c_str();
        outFile.open(outputFileNameChar); // Open the file
*/

        if (!InputDoc.LoadFile(filename)) {
            System::Logger::printError(outFile, InputDoc.ErrorDesc());
        }

        parseSuccessful = this->parse(outFile);

        ENSURE(properlyInitialized(), "Parser not properly initialized");
    }


    bool XMLParser::parse(std::ostream &errorstream) {

        REQUIRE(properlyInitialized(), "XMLParser was not properly initialized when attempting to call parse");

        TiXmlElement *System = InputDoc.FirstChildElement();

        bool consistent = true;


        REQUIRE(System != nullptr, "There is no system in xml");


        for (TiXmlElement *Level1Elem = System->FirstChildElement(); Level1Elem != nullptr;
             Level1Elem = Level1Elem->NextSiblingElement()) {

            std::string type_sys = Level1Elem->Value();


            if (type_sys == "DEVICE") {
                bool readingCorrect = true;
                std::string name;
                int emissions, speed;
                std::string type;
                float cost;

                for (TiXmlElement *elem = Level1Elem->FirstChildElement(); elem != nullptr;
                     elem = elem->NextSiblingElement()) {

                    std::string elemname = elem->Value();
                    std::string test;


                    if (elem->FirstChild() == nullptr) {
                        readingCorrect = false;
                        System::Logger::printError(errorstream, elemname + " should not be empty");
                        break;

                    } else {

                        if (elemname == "name") {


                            std::string name_t = elem->FirstChild()->ToText()->Value();


                            if (name_t.empty()) {
                                std::string type_err = "Name";
                                System::Logger::parseNameEmpty(errorstream, type_err);
                                readingCorrect = false;
                                break;


                            } else {
                                name = name_t;

                            }


                        } else if (elemname == "emissions") {

                            if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                                emissions = std::stoi(elem->FirstChild()->ToText()->Value());

                            } else {


                                std::string type_err = "Emissions";
                                System::Logger::parseNegative(errorstream, type_err);
                                readingCorrect = false;
                                consistent = false;
                                break;

                                //return readingCorrect;


                            }
                        } else if (elemname == "cost") {

                            if (std::stof(elem->FirstChild()->ToText()->Value()) > 0) {
                                cost = std::stof(elem->FirstChild()->ToText()->Value());

                            } else {
                                std::string type_err = "Cost";
                                System::Logger::parseNegative(errorstream, type_err);
                                readingCorrect = false;
                                consistent = false;
                                break;
                                //return readingCorrect;


                            }

                        } else if (elemname == "type") {


                            std::string type_d = elem->FirstChild()->ToText()->Value();


                            if (type_d.empty()) {
                                std::string type_err = "Type";
                                System::Logger::parseNameEmpty(errorstream, type_err);
                                readingCorrect = false;
                                break;
                                //return readingCorrect;

                            } else {
                                if (type_d == "bw" || type_d == "scan" || type_d == "color") {
                                    type = type_d;

                                } else {
                                    System::Logger::printError(errorstream, "Invalid type for device");
                                    readingCorrect = false;
                                    break;
                                }

                            }

                        } else if (elemname == "speed") {
                            if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                                speed = std::stoi(elem->FirstChild()->ToText()->Value());
                            } else {
                                std::string type_err = "Speed";
                                System::Logger::parseNegative(errorstream, type_err);

                                readingCorrect = false;
                                consistent = false;
                                break;

                            }

                        } else {

                            System::Logger::printError(errorstream, "Element name " + elemname +
                                                                    " is either empty or an unexpected element name");
                            readingCorrect = false;
                            break;
                        }

                    }
                }
                if (readingCorrect) {

                    Device *outPtr = nullptr;

                    if (type == "color") {
                        if (emissions <= 23) {
                            outPtr = new CPrinter(name, emissions, speed, cost);
                        } else {
                            System::Logger::exceededLimits(errorstream, name);
                        }
                    } else if (type == "bw") {
                        if (emissions <= 8) {
                            outPtr = new BWPrinter(name, emissions, speed, cost);
                        } else {
                            System::Logger::exceededLimits(errorstream, name);
                        }
                    } else if (type == "scan") {
                        if (emissions <= 12) {
                            outPtr = new Scanner(name, emissions, speed, cost);
                        } else {
                            System::Logger::exceededLimits(errorstream, name);
                        }
                    }


                    if (outPtr != nullptr) {

                        deviceList.push_back(outPtr);
                    }
                } else {
                    System::Logger::printError(errorstream, "there was an error in a device in the inputfile");

                }


            } else if (type_sys == "JOB") {
                std::string userName;
                int pageCount, jobNr;
                std::string type;
                bool readingCorrectly = true;

                for (TiXmlElement *elem = Level1Elem->FirstChildElement(); elem != nullptr;
                     elem = elem->NextSiblingElement()) {


                    std::string elemname = elem->Value();


                    if (elemname == "userName") {
                        TiXmlNode *t = elem->FirstChild();
                        if (t == nullptr) {
                            std::string type_err = "Username";
                            System::Logger::parseNameEmpty(errorstream, type_err);
                            readingCorrectly = false;
                            break;
                            //return readingCorrectly;
                        } else {
                            std::string userName_t = elem->FirstChild()->ToText()->Value();
                            userName = userName_t;

                        }

                    } else if (elemname == "pageCount") {
                        if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                            pageCount = std::stoi(elem->FirstChild()->ToText()->Value());
                        } else {
                            std::string type_err = "Pagecount";
                            System::Logger::parseNegative(errorstream, type_err);
                            consistent = false;
                            readingCorrectly = false;
                            break;
                            //return readingCorrectly;
                        }


                    } else if (elemname == "jobNumber") {
                        if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                            jobNr = std::stoi(elem->FirstChild()->ToText()->Value());
                        } else {
                            std::string type_err = "Jobnumber";
                            System::Logger::parseNegative(errorstream, type_err);
                            consistent = false;
                            readingCorrectly = false;
                            break;
                            //return readingCorrectly;
                        }


                    } else if (elemname == "type") {


                        std::string type_j = elem->FirstChild()->ToText()->Value();


                        if (type_j.empty()) {
                            std::string type_err = "Type";
                            System::Logger::parseNameEmpty(errorstream, type_err);
                            readingCorrectly = false;
                            break;
                            //return readingCorrectly;

                        } else {
                            if (type_j == "bw" || type_j == "scan" || type_j == "color") {
                                type = type_j;
                            } else {
                                System::Logger::printError(errorstream, "Invalid type for job");
                                readingCorrectly = false;
                                break;
                            }

                        }

                    } else {
                        System::Logger::printError(errorstream, "Element name " + elemname +
                                                                " is either empty or an unexpected element name");
                        readingCorrectly = false;
                        break;
                    }
                }

                if (readingCorrectly) {


                    if (jobNrSet.count(jobNr) == 0) {

                        //Job is only added to joblist if its jobnr is unique
                        Job tempJob = Job(userName, pageCount, jobNr, type);


                        Job *outJobPtr = nullptr;

                        if (type == "bw") {
                            outJobPtr = new BWJob(userName, pageCount, jobNr);
                        } else if (type == "color") {
                            outJobPtr = new CJob(userName, pageCount, jobNr);
                        } else if (type == "scan") {
                            outJobPtr = new ScanJob(userName, pageCount, jobNr);
                        }

                        //ownSystem->addJob(outJobPtr);

                        jobList.push_back(outJobPtr);
                        jobNrSet.insert(jobNr);

                    } else {

                        System::Logger::printError(errorstream, "Jobnumber should be unique");
                        consistent = false;
                        //return false;
                    }

                } else {

                    System::Logger::printError(errorstream, "there was an error in a device in the inputfile");
                }


            } else {

                System::Logger::printError(errorstream, "Element should be either a printer or a Job, is a " + type_sys);



                continue;

            }


        }


        return consistent;
    }


    bool XMLParser::properlyInitialized() const {
        return (this == _initCheck);
    }

    std::vector<Device *> *XMLParser::getDeviceList() {
        REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getDeviceList()");
        return &deviceList;
    }

    std::vector<Job *> *XMLParser::getJobList() {
        REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getJobList()");
        return &jobList;
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
        REQUIRE(filename != nullptr, "File should be properly given");


        std::ofstream outFile; // Create an output file stream
        std::string f = filename;
        std::string outputFileName = f + ".txt";
        const char *outputFileNameChar = outputFileName.c_str();
        outFile.open(outputFileNameChar); // Open the file

        if (InputDoc.LoadFile(filename)) {

            System::Logger::printError(outFile, InputDoc.ErrorDesc());

        }

        parseSuccessful = this->parse(outFile);
        return parseSuccessful;

    }

    bool XMLParser::isConsistent() const {
        REQUIRE(properlyInitialized(), "Parser not properly initialized when checking for consistency");

        return parseSuccessful;
    }

} // System