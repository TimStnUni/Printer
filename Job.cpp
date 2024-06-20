//
// Created by tim on 18/04/24.
//

#include "Job.h"
#include "Device.h"

namespace System {

    Job::Job(std::string userName_in, int pageCount_in, int jobNr_in, std::string type_in) {

        REQUIRE(!userName_in.empty(), "Username shouldn't be empty");
        REQUIRE(pageCount_in > 0, "Pagecount should be positive");
        REQUIRE(!type_in.empty(), "Type should not be empty");

        _initCheck = this;

        this->setUserName(userName_in);
        this->setPageCount(pageCount_in);
        this->setJobNr(jobNr_in);
        this->setType(type_in);


        ENSURE(this->properlyInitialized(), "Job wasn't properly initialized");


    }

    unsigned int Job::getJobNr() const {
        REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getJobNr()");
        return jobNr;
    }

    std::string Job::getUserName() const {
        REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getUserName()");
        return userName;
    }

    int Job::getPageCount() const {
        REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getPageCount()");
        return pageCount;
    }

    std::string Job::getType() const {

        REQUIRE(this->properlyInitialized(), "Job not initialized when calling getType()");
        return type;
    }

    Job::Job() {

        _initCheck = this;
        ENSURE(this->properlyInitialized(), "Default constructor not properly initialized");
    }

    bool Job::properlyInitialized() const {
        return this == _initCheck;
    }

    Job::Job(const Job &inJob) {




        _initCheck = this;

        this->setUserName(inJob.getUserName());
        this->setJobNr(inJob.getJobNr());
        this->setPageCount(inJob.getPageCount());
        this->setType(inJob.getType());
        this->setOwnDevice(inJob.getOwnDevice());


        /*
         * Pointer bullshittery that should no longer be needed
        if (inJob.getOwnDevice() != nullptr) {
            this->ownerDevice->updatePointer(this, &inJob);
        }
        */
        ENSURE(this->properlyInitialized(), "job was not properly initialized");
    }


    void Job::setJobNr(int jobNr_in) {
        REQUIRE(jobNr_in > 0, "jobnr should be positive");

        this->jobNr = jobNr_in;

        ENSURE(this->getJobNr() == jobNr_in, "Jobnr not correctly set");
    }

    void Job::setPageCount(int pageCount_in) {
        REQUIRE(pageCount_in > 0, "Pagecount should be positive");

        this->pageCount = pageCount_in;
        this->currentPageCount = pageCount;

        ENSURE(this->getPageCount() == pageCount_in, "Pagecount not correctly set");
    }

    void Job::setUserName(const std::string &userName_in) {
        REQUIRE(!userName_in.empty(), "Username should not be empty");

        this->userName = userName_in;

        ENSURE(this->getUserName() == userName_in, "Username not correctly set");
    }

    void Job::setType(const std::string type_in) {
        REQUIRE(!type_in.empty(), "Type should not be empty");
        this->type = type_in;
        ENSURE(this->getType() == type_in, "Type not correctly set");
    }



    Job &Job::operator=(const Job &inJob) {

        //I'm ninety percent sure this doesn't work anymore, but atm it isn't used so it should be fine

        std::cout << "Assignment operator called for job " << inJob.getJobNr() << std::endl;
        Job outJob(inJob.getUserName(), inJob.getPageCount(), inJob.getJobNr(), inJob.type);


        //Pointer bullshittery that should no longer be needed
        //outJob.setOwnDevice(inJob.getOwnDevice());



        //outJob._initCheck = &outJob;


        return *this;
    }

    void Job::setOwnDevice(System::Device *ownDevice) {

        REQUIRE(properlyInitialized(), "Job not properly initialized when attempting to set owner device");
        REQUIRE(ownDevice != nullptr, "Input pointer should definitely not be a nullptr");

        this->ownerDevice = ownDevice;

        ENSURE(this->getOwnDevice() == ownDevice, "ownerDevice not correctly set");

    }

    System::Device *Job::getOwnDevice() const{

        REQUIRE(properlyInitialized(), "Job nor properly initialized when attempting to get owner device");
        REQUIRE(this->ownerDevice != nullptr, "own device should definitely not be the nullptr");
        return this->ownerDevice;
    }

    bool Job::printPage() {

        if (currentPageCount > 0) {

            currentPageCount--;
            return false;
        }else{

            //std::cout << "job has been fully printed" << std::endl;
            return true;
        }


    }

    int Job::printFull() {


        int remPages = this->getRemainingPages();

        while(!printPage());

        ownerDevice->removeJob(this);

        return (this->getOwnDevice()->getEmissions() * remPages);

    }

    unsigned int Job::getPrintedPages() const {
        return pageCount - currentPageCount;
    }

    int Job::printPages(unsigned int amount) {

        if (amount >= currentPageCount) {

            for (int i = 0; i < amount; i++) {

                this->printPage();

            }
            return amount * this->getOwnDevice()->getEmissions();
        }else{

            int remPages = this->getRemainingPages();
            logger.pageAmount(std::cout);
            while(!printPage());
            ownerDevice->removeJob(this);

            return remPages * this->getOwnDevice()->getEmissions();
        }

    }

    unsigned int Job::getRemainingPages() const {
        return currentPageCount;
    }


} // System