//
// Created by tim on 18/04/24.
//

#ifndef PROJSOFTENG_JOB_H
#define PROJSOFTENG_JOB_H
#include <iostream>
#include <string>
#include "DesignByContract.h"
namespace System {

    class Job {

    public:
        /**
         * \brief Default Constructor
         */
        Job();

        /**
         * \brief Copy constructor to fix _initcheck to this
         * @param inJob
         */

        Job(const Job &inJob);

        /**
         * \brief Usual constructor for a printing job
         * @param userName_in Username of the owner of the printing job
         * @param pageCount_in How many pages need to be printed
         * @param jobNr_in JobNr for the job
         *
         *REQUIRE(!userName_in.empty(), "Username shouldn't be empty");
         *REQUIRE(pageCount_in>0, "Pagecount should be positive");
         *
         * ENSURE(this->properlyInitialized(), "Job wasn't properly initialized")
         */
        Job(std::string userName_in, int pageCount_in, int jobNr_in);


        /**
         * \brief Getter function for the jobnr
         * @return unsigned integer version of the jobnr, these should theoretically always be positive, though this is not required by the standard
         * REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getJobNr()")
         */
        unsigned int getJobNr()const;

        /**
         * \brief Getter function for the Username
         * @return username as a string
         * REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getUserName()")
         */
        std::string getUserName()const;

        /**
         * \brief Getter function for the PageCount
         * @return
         * REQUIRE(this->properlyInitialized(), "Job wasn't initialized when calling getPageCount()")
         */
        int getPageCount()const;


        /**
         * \brief Setter function for jobNr
         * @param jobNr
         * REQUIRE(jobNr_in>0, "jobnr should be positive")
         * ENSURE(this->getJobNr() == jobNr_in, "Jobnr not correctly set")
         */

        void setJobNr(int jobNr);

        /**
         * \brief Setter function for the pagecount
         * @param pageCount
         * REQUIRE(pageCount_in > 0, "Pagecount should be positive")
         * ENSURE(this->getPageCount() == pageCount_in, "Pagecount not correctly set")
         */

        void setPageCount(int pageCount);


        /**
         * \brief Setter function for username
         * @param userName
         * REQUIRE(!userName_in.empty(), "Username should not be empty")
         * ENSURE(this->getUserName() == userName_in, "Username not correctly set")
         */
        void setUserName(const std::string &userName);



        /**
         * Overload of the = constructor for jobs since it seems to be needed for something
         * @param inJob
         * @return
         */

        Job& operator=(Job const & inJob);

    private:
        int jobNr, pageCount;
        std::string userName;
        Job *_initCheck;

        bool properlyInitialized() const;




    };

} // System

#endif //PROJSOFTENG_JOB_H
