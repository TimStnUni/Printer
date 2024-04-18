//
// Created by tim on 18/04/24.
//

#include "Job.h"

namespace System {

    Job::Job(std::string userName_in, int pageCount_in, int jobNr_in) {

        REQUIRE(!userName_in.empty(), "Username shouldn't be empty");
        REQUIRE(pageCount_in > 0, "Pagecount should be positive");


        _initCheck = this;

        this->setUserName(userName_in);
        this->setPageCount(pageCount_in);
        this->setJobNr(jobNr_in);


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

        ENSURE(this->getPageCount() == pageCount_in, "Pagecount not correctly set");
    }

    void Job::setUserName(const std::string &userName_in) {
        REQUIRE(!userName_in.empty(), "Username should not be empty");

        this->userName = userName_in;

        ENSURE(this->getUserName() == userName_in, "Username not correctly set");
    }

    Job &Job::operator=(const Job &inJob) {
        Job outJob;
        outJob.userName = inJob.getUserName();
        outJob.pageCount = inJob.getPageCount();
        outJob.jobNr = inJob.getJobNr();
        outJob._initCheck = &outJob;
        return *this;
    }



} // System