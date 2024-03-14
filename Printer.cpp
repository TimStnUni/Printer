//
// Created by tim on 29/02/24.
//

#include "Printer.h"

namespace Printer {

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

        //Step 3 of the use case still needs to be checked. I believe this needs to be done in the printer class.
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

        //Todo: replace all direct assignments with setters (so first implement setters)

        for (TiXmlElement *Level1Elem = System->FirstChildElement(); Level1Elem != NULL;
             Level1Elem = Level1Elem->NextSiblingElement()) {

            std::string type = Level1Elem->Value();


            //Todo: Replace all straight assignments with a setter function?
            //Can technically move checks into those functions? is this better?

            if (type == "DEVICE") {
                bool readingCorrect = true;
                std::string name;
                int emissions, speed;

                for (TiXmlElement *elem = Level1Elem->FirstChildElement(); elem != NULL;
                     elem = elem->NextSiblingElement()) {

                    std::string elemname = elem->Value();


                    if (elemname == "name") {
                        std::string name_t = elem->FirstChild()->ToText()->Value();
                        if (name_t.empty()) {
                            std::cout << "Name should not be empty" << std::endl;
                            readingCorrect = false;
                            continue;

                        } else {
                            name = name_t;
                        }


                    } else if (elemname == "emissions") {

                        if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                            emissions = std::stoi(elem->FirstChild()->ToText()->Value());
                        } else {
                            std::cout << "Emissions should be positive" << std::endl;
                            readingCorrect = false;
                            continue;


                        }


                    } else if (elemname == "speed") {
                        if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                            speed = std::stoi(elem->FirstChild()->ToText()->Value());
                        } else {
                            std::cout << "speed should be positive" << std::endl;
                            readingCorrect = false;
                            continue;
                        }

                    } else {
                        std::cout << "Element name " << elemname << " is either empty or an unexpected element name"
                                  << std::endl;
                        readingCorrect = false;
                        continue;
                    }
                }

                if (readingCorrect) {
                    Device tempPrinter = Device(name, emissions, speed);
                    deviceList.push_back(tempPrinter);
                }
            }
                //This entire else if statement has to be redone, since there are multiple username. at the start it should probably
                //make a job class and push stuff into there
                //That would remove a bunch of the unneeded data members now as well

                //Could potentially have the job be made at the end, after checks have been completed? probably better
                //Maybe introduce some bool "ReadingCorrectly" that gets put to false if ever a member is not read correctly?
                //is this even necessary with the continue statements?
            else if (type == "JOB") {
                std::string userName;
                int pageCount, jobNr;
                bool readingCorrectly = true;

                for (TiXmlElement *elem = Level1Elem->FirstChildElement(); elem != NULL;
                     elem = elem->NextSiblingElement()) {


                    std::string elemname = elem->Value();


                    if (elemname == "userName") {
                        std::string userName_t = elem->FirstChild()->ToText()->Value();
                        if (userName_t.empty()) {
                            std::cout << "username should not be empty" << std::endl;
                            readingCorrectly = false;
                            continue;
                        } else {
                            userName = userName_t;

                        }

                    } else if (elemname == "pageCount") {
                        if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                            pageCount = std::stoi(elem->FirstChild()->ToText()->Value());
                        } else {
                            std::cout << "pagecount should be a positive integer" << std::endl;
                            readingCorrectly = false;
                            continue;
                        }


                    } else if (elemname == "jobNumber") {
                        if (std::stoi(elem->FirstChild()->ToText()->Value()) > 0) {
                            jobNr = std::stoi(elem->FirstChild()->ToText()->Value());
                        } else {
                            //Not actually sure this needs to be a positive integer
                            std::cout << "jobnumber should be a positive integer" << std::endl;
                            readingCorrectly = false;
                            continue;
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
                        Job tempJob = Job(userName, pageCount, jobNr);
                        jobList.push_back(tempJob);
                        jobNrMap.insert({jobNr, jobList.size() - 1});
                        jobNrSet.insert(jobNr);

                    } else {

                        std::cout << "jobnr should be unique" << std::endl;
                    }

                }


            } else {

                std::cerr << "Element should be either a printer or a Job, is a " << type << std::endl;


                continue;

            }


        }


    }

/*
    std::string XMLParser::getName() {
        REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getName()");
        return name;
    }

    int XMLParser::getSpeed() {
        REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getSpeed()");
        return speed;
    }

    int XMLParser::getEmissions() {
        REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getEmissions()");
        return emissions;
    }
*/
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


    }

    int XMLParser::getNrOfJobs() {
        REQUIRE(this->properlyInitialized(), "Parser not properly initialized when calling getNrOfJobs()");
        return jobList.size();
    }

    std::set<unsigned int> XMLParser::getJobNrSet() {
        return jobNrSet;
    }


    Device::Device(std::string name_in, int emissions_in, int speed_in) {

        //REQUIRE(emissions_in > 0, "Emissions should be positive");
        //REQUIRE(speed_in > 0, "Speed should be positive");

        name = name_in;
        emissions = emissions_in;
        speed = speed_in;

        _initCheck = this;
        ENSURE(this->properlyInitialized(), "Device is not properly initialized");
    }

    Device::Device() {
        _initCheck = this;

        ENSURE(this->properlyInitialized(), "device was not properly initialized in the default constructor");

    }

    std::string Device::getNameDev() {

        REQUIRE(this->properlyInitialized(), "Device not initialized when calling getNameDev()");
        //This require is not satisfied. I believe this may be because of a copy constructor not setting _initcheck

        return name;
    }

    int Device::getEmissions() {
        //REQUIRE(this->properlyInitialized(), "Device not initialized when calling getEmissions()");
        return emissions;
    }

    int Device::getSpeed() {
        //REQUIRE(this->properlyInitialized(), "Device not initialized when calling getSpeed()");
        return speed;
    }

    bool Device::properlyInitialized() {
        return (this == _initCheck);
    }

    Device::Device(const Device &inDevice) {

        name = inDevice.name;
        emissions = inDevice.emissions;
        speed = inDevice.speed;

        _initCheck = this;


        ENSURE(this->properlyInitialized(), "Device not properly initialized in copy constructor");


    }





    ///////////////////////////////////////////////////////////
    //
    //
    //////////////////////////////////////////////////////////

    Job::Job(std::string userName_in, int pageCount_in, int jobNr_in) {

        userName = userName_in;
        pageCount = pageCount_in;
        jobNr = jobNr_in;

        _initCheck = this;

        ENSURE(this->properlyInitialized(), "Job wasn't properly initialized");


    }

    unsigned int Job::getJobNr() {
        //REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getJobNr()");
        return jobNr;
    }

    std::string Job::getUserName() {
        //REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getUserName()");
        return userName;
    }

    int Job::getPageCount() {
        //REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getPageCount()");
        return pageCount;
    }

    Job::Job() {
        _initCheck = this;
    }

    bool Job::properlyInitialized() {
        return this == _initCheck;
    }

    Job::Job(const Job &inJob) {

        userName = inJob.userName;
        pageCount = inJob.pageCount;
        jobNr = inJob.jobNr;


        _initCheck = this;
        ENSURE(this->properlyInitialized(), "job was not properly initialized");
    }

    Printer::Printer() {

        _initCheck = this;

        ENSURE(this->properlyInitialized(), "Printer was not properly initialized");

    }

    void Printer::addDevices(std::vector<Device> device_in) {

        REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling addDevices()");

        //deviceList.insert(deviceList.end(), device_in.begin(), device_in.end());

        deviceList = device_in;
    }

    void Printer::addJobs(std::deque<Job> &jobs, std::map<unsigned int, unsigned int> &jobnrs, std::set<unsigned int> & jobNrSet) {
        REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling addJobs()");

        /*
        jobList.insert(jobList.end(), jobs.begin(), jobs.end());

        for (std::unordered_set<unsigned int>::iterator it = jobnrs.begin(); it != jobnrs.end(); it++) {

            jobNrSet.insert(*it);

        }
         */

        jobList = jobs;
        jobNrMap = jobnrs;
        this->jobNrSet = jobNrSet;



    }

    Device Printer::getDevice() {
        return deviceList.at(0);
    }

    std::deque<Job> Printer::getJobList() {
        return jobList;
    }

    std::map<unsigned int, unsigned int> Printer::getJobNrMap() {
        return jobNrMap;
    }

    bool Printer::properlyInitialized() {
        return (this == _initCheck);
    }


    Printer::Printer(const Printer &inPrinter) {

        jobList = inPrinter.jobList;
        jobNrMap = inPrinter.jobNrMap;

        deviceList = inPrinter.deviceList;


        _initCheck = this;


    }

    std::set<unsigned int> Printer::getJobNrSet() {
        return jobNrSet;
    }

    unsigned int Printer::getJobIndex(unsigned int &jobNr) {
        return jobNrMap.at(jobNr);
    }

    void Printer::removeJob(unsigned int jobNr) {

        jobList.erase(jobList.begin() + jobNrMap.at(jobNr));


    }

    PrinterSystem::PrinterSystem() {


        _initcheck = this;


    }

    void PrinterSystem::readXML(const char *filename) {

        XMLParser tempXML(filename);

        Printer tempPrtr;

        tempPrtr.addDevices(tempXML.getDeviceList());

        std::map<unsigned int, unsigned int> jobnrs = tempXML.getJobNrMap();
        std::deque<Job> tempJobList = tempXML.getJobList();
        std::set<unsigned int> tempJobSet = tempXML.getJobNrSet();
        tempPrtr.addJobs(tempJobList, jobnrs, tempJobSet);


        printerList.push_back(tempPrtr);

        int printerIndex = printerList.size() - 1;


        std::set<unsigned int>::iterator it;


        for (it = tempJobSet.begin(); it != tempJobSet.end(); ++it) {


            if (jobNrSet.find(*it) == jobNrSet.end()) {

                jobNrMap.insert({*it, printerIndex});
                jobNrSet.insert(*it);

            }
            else {


                //todo : Expand on this error
                std::cout << "JobNr is not unique" << std::endl;
            }

        }


    }

    void PrinterSystem::getInfo(std::string filename) {

        REQUIRE(properlyInitialized(), "the printer system was not properly initialized");


        std::ofstream outfile;
        outfile.open(filename);
        if (!outfile.is_open()) {
            std::cout << "file could not be opened" << std::endl;
        }


        Device currentPrinter;
        for (std::vector<Printer>::iterator printIt = printerList.begin(); printIt != printerList.end(); ++printIt) {



            //This specific copying is where the issue lies. It's simply the only copying after which we use a member function.
            currentPrinter = printIt->getDevice();


            outfile << currentPrinter.getNameDev() << " (CO2: " << currentPrinter.getEmissions() << "g/page; speed "
                    << currentPrinter.getSpeed() << "p/minute):\n";

            std::deque<Job> currentJobs = printIt->getJobList();

            for (std::deque<Job>::iterator jobIt = currentJobs.begin(); jobIt != currentJobs.end(); ++jobIt) {

                if (jobIt == currentJobs.begin()) {

                    outfile << "    * Current: \n";
                } else {
                    outfile << "    * Queue: \n";
                }

                outfile << "        [#" << jobIt->getJobNr() << "|" << jobIt->getUserName() << "|"
                        << jobIt->getPageCount()
                        << "]\n";

            }


            outfile << std::endl;
        }


        outfile.close();

    }

    bool PrinterSystem::properlyInitialized() {
        return (this == _initcheck);
    }

    void PrinterSystem::doPrintJob(unsigned int jobnr) {

        int printerindex = jobNrMap.at(jobnr);

        Printer Currentprinter = printerList.at(printerindex);

        Device currentDevice = Currentprinter.getDevice();

        std::set<unsigned int> currentJobNrList = Currentprinter.getJobNrSet();


        unsigned int jobnrindex = Currentprinter.getJobIndex(jobnr);

        Job currentJob = Currentprinter.getJobList().at(jobnrindex);


        int pages = currentJob.getPageCount();

        while (pages > 0) {
            pages--;
        }

        std::cout << "Printer \"" << currentDevice.getNameDev() << "\" finished job:\n";
        std::cout << "  Number: " << jobnr << "\n";
        std::cout << "  Submitted by \"" << currentJob.getUserName() << "\"\n";
        std::cout << "  " << currentJob.getPageCount() << " pages\n";

        std::cout << std::endl;
        printerList.at(printerindex).removeJob(jobnr);


    }

    void PrinterSystem::printAll() {

        for (std::set<unsigned int>::iterator jobNrIt = jobNrSet.begin(); jobNrIt != jobNrSet.end(); jobNrIt++){

            this->doPrintJob(*jobNrIt);
        }

    }
} // Printer