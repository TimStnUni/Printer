//
// Created by tim on 29/02/24.
//

#include "Printer.h"

namespace Printer {


    /////////////////////////////////////////////////////////////////
    //
    //
    //XMLPARSER
    //
    ////////////////////////////////////////////////////////////////////

    XMLParser::XMLParser(const char *filename) {

        //Todo: check whether inputdoc isn't empty
        if (InputDoc.LoadFile(filename)) {
            std::cerr << InputDoc.ErrorDesc() << std::endl;
        }

        _initCheck = this;
        this->parse();

        ENSURE(properlyInitialized(), "Parser not properly initialized");

    }


    void XMLParser::parse() {

        TiXmlElement *System = InputDoc.FirstChildElement();

        REQUIRE(System != nullptr, "There is no system in xml");


        for (TiXmlElement *Level1Elem = System->FirstChildElement(); Level1Elem != NULL;
             Level1Elem = Level1Elem->NextSiblingElement()) {

            std::string type = Level1Elem->Value();


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
            } else if (type == "JOB") {
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

    void XMLParser::addInputFile(const char *filename) {

        REQUIRE(this->properlyInitialized(), "Parser wasn't properly initialized when calling addInputFile");

        if (InputDoc.LoadFile(filename)) {
            std::cerr << InputDoc.ErrorDesc() << std::endl;
        }

        this->parse();


    }


    Device::Device(std::string name_in, int emissions_in, int speed_in) {

        //REQUIRE(emissions_in > 0, "Emissions should be positive");
        //REQUIRE(speed_in > 0, "Speed should be positive");

        _initCheck = this;


        this->setNameDev(name_in);
        this->setEmissions(emissions_in);
        this->setSpeed(speed_in);

        ENSURE(this->properlyInitialized(), "Device is not properly initialized");
    }

    Device::Device() {
        _initCheck = this;

        ENSURE(this->properlyInitialized(), "device was not properly initialized in the default constructor");

    }

    std::string Device::getNameDev() const{

        REQUIRE(this->properlyInitialized(), "Device not initialized when calling getNameDev()");
        return name;
    }

    int Device::getEmissions() const{
        REQUIRE(this->properlyInitialized(), "Device not initialized when calling getEmissions()");
        return emissions;
    }

    int Device::getSpeed() const{
        REQUIRE(this->properlyInitialized(), "Device not initialized when calling getSpeed()");
        return speed;
    }

    bool Device::properlyInitialized() const{
        return (_initCheck == this);
    }

    Device::Device(const Device &inDevice) {


        _initCheck = this;


        std::string inName = inDevice.getNameDev();
        int emissions_in = inDevice.getEmissions();
        int speed_in = inDevice.getSpeed();


        this->setNameDev(inName);
        this->setEmissions(emissions_in);
        this->setSpeed(speed_in);



        ENSURE(this->properlyInitialized(), "Device not properly initialized in copy constructor");


    }

    void Device::setNameDev(std::string &inName) {


        REQUIRE(!inName.empty(), "name shouldn't be empty");
        this->name = inName;

        ENSURE(this->getNameDev() == inName, "Name not correctly set");

    }

    void Device::setEmissions(int &emissions_in) {

        REQUIRE(emissions_in > 0, "Emissions should be positive");
        this->emissions = emissions_in;
        ENSURE(this->getEmissions() == emissions_in, "Emissions not correctly set");

    }

    void Device::setSpeed(int &speed_in) {

        REQUIRE(speed_in > 0, "Speed should be positive");

        this->speed = speed_in;

        ENSURE(this->getSpeed() == speed_in, "Speed not correctly set");

    }





    ///////////////////////////////////////////////////////////
    //
    //
    //////////////////////////////////////////////////////////

    Job::Job(std::string userName_in, int pageCount_in, int jobNr_in) {

        REQUIRE(!userName_in.empty(), "Username shouldn't be empty");
        REQUIRE(pageCount_in>0, "Pagecount should be positive");


        _initCheck = this;

        this->setUserName( userName_in);
        this->setPageCount(pageCount_in);
        this->setJobNr( jobNr_in);



        ENSURE(this->properlyInitialized(), "Job wasn't properly initialized");


    }

    unsigned int Job::getJobNr() const{
        REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getJobNr()");
        return jobNr;
    }

    std::string Job::getUserName() const{
        REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getUserName()");
        return userName;
    }

    int Job::getPageCount() const{
        REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getPageCount()");
        return pageCount;
    }

    Job::Job() {
        _initCheck = this;
        ENSURE(this->properlyInitialized(), "Default constructor not properly initialized");
    }

    bool Job::properlyInitialized() const{
        return this == _initCheck;
    }

    Job::Job(const Job &inJob) {

        _initCheck = this;

        this->setUserName(inJob.getUserName());
        this->setJobNr(inJob.getJobNr());
        this->setPageCount(inJob.getPageCount());


        ENSURE(this->properlyInitialized(), "job was not properly initialized");
    }

    void Job::setJobNr(int jobNr_in) {
        REQUIRE(jobNr_in>0, "jobnr should be positive");

        this->jobNr = jobNr_in;

        ENSURE(this->getJobNr() == jobNr_in, "Jobnr not correctly set");
    }

    void Job::setPageCount(int pageCount_in) {
        REQUIRE(pageCount_in > 0, "Pagecount should be positive");

        this->pageCount = pageCount_in;

        ENSURE(this->getPageCount() == pageCount_in, "Pagecount not correctly set");
    }

    void Job::setUserName(const std::string &userName_in) {
        REQUIRE(!userName_in.empty(), "Username should not be empty");

        this->userName = userName_in;

        ENSURE(this->getUserName() == userName_in, "Username not correctly set");
    }

    Printer::Printer() {

        _initCheck = this;

        ENSURE(this->properlyInitialized(), "Printer was not properly initialized");

    }

    void Printer::addDevices(std::vector<Device> device_in) {

        REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling addDevices()");



        deviceList.insert(deviceList.end(), device_in.begin(), device_in.end());


        for (int i = 0; i < device_in.size(); i++) {
            Device tempDev = device_in.at(i);
            ENSURE(this->getDevice(deviceList.size() - device_in.size() + i) == tempDev, "Device was added correctly");
        }
    }

    void Printer::addJobs(std::deque<Job> &jobs, std::map<unsigned int, unsigned int> &jobnrs,
                          std::set<unsigned int> &jobNrSet) {
        REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling addJobs()");


        jobList.insert(jobList.end(), jobs.begin(), jobs.end());

        for (std::set<unsigned int>::iterator it = jobNrSet.begin(); it != jobNrSet.end(); it++) {

            jobNrSet.insert(*it);

        }

        for (std::map<unsigned int, unsigned int>::iterator mapIt = jobnrs.begin(); mapIt!=jobnrs.end(); mapIt++){

            jobNrMap.insert({mapIt->first, mapIt->second});

        }



        //Todo: Add a ensure here in the style of addDevices


    }

    Device Printer::getDevice(int index) {
        REQUIRE(this->properlyInitialized(), "printer wasn't properly initialized when calling getDevice()");

        return deviceList.at(index);
    }

    std::deque<Job> Printer::getJobList() {
        REQUIRE(this->properlyInitialized(), "printer wasn't properly initialized when calling getDevice()");
        return jobList;
    }

    std::map<unsigned int, unsigned int> Printer::getJobNrMap() {
        REQUIRE(this->properlyInitialized(), "printer wasn't properly initialized when calling getDevice()");
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


        unsigned int jobindex = jobNrMap.at(jobNr);
        jobNrMap.erase(jobNr);




        for (std::map<unsigned int, unsigned int>::iterator jobMapIt = jobNrMap.begin(); jobMapIt !=jobNrMap.end(); jobMapIt++){
            if (jobMapIt->second > jobindex){
               jobMapIt->second = jobMapIt->second - 1;
            }

        }


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

            } else {


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


        for (std::vector<Printer>::iterator printIt = printerList.begin(); printIt != printerList.end(); ++printIt) {


            Device currentPrinter = printIt->getDevice(0);


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

        Device currentDevice = Currentprinter.getDevice(0);

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
        jobNrSet.erase(jobnr);
        jobNrMap.erase(jobnr);


    }

    void PrinterSystem::printAll() {

        for (std::set<unsigned int>::iterator jobNrIt = jobNrSet.begin(); jobNrIt != jobNrSet.end(); jobNrIt++) {

            this->doPrintJob(*jobNrIt);

        }

    }
} // Printer