//
// Created by tim on 18/04/24.
//

#ifndef PROJSOFTENG_JOB_H
#define PROJSOFTENG_JOB_H
#include <iostream>
#include <string>
#include "DesignByContract.h"
namespace System {

    class Device;
    class Job {

    public:
        /**
         * \brief Default Constructor
         * ENSURE(this->properlyInitialized(), "Default constructor not properly initialized")
         */
        Job();

        /**
         * \brief Copy constructor
         * @param inJob
         * ENSURE(this->properlyInitialized(), "job was not properly initialized")
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
         *REQUIRE(!type_in.empty(), "Type should not be empty")
         * ENSURE(this->properlyInitialized(), "Job wasn't properly initialized")
         */
        Job(std::string userName_in, int pageCount_in, int jobNr_in, std::string type_in);


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
         * \brief Setter function for ownerDevice
         * @param ownDevice
         *  REQUIRE(properlyInitialized(), "Job not properly initialized when attempting to set owner device");
         * ENSURE(this->getOwnDevice() == ownDevice, "OwnDevice not correctly set")
         */

        void setOwnDevice(System::Device * ownDevice);


        /**
         * \brief getter function for ownerDevice
         * @return
         * REQUIRE(properlyInitialized(), "Job nor properly initialized when attempting to get owner device");
         *
         */
        System::Device * getOwnDevice() const;

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

        //TODO:: filled it in, has to get checked
        /**
         * \brief A setter function for the printer speed
         * @param type_in
         * REQUIRE(!type_in.empty(), "Type should not be empty")
         * ENSURE(this->getType() == type_in, "Type not correctly set")
         */

        void setType(std::string type_in);
        /**
         * \brief a getter function for the device type
         * @return returns the type of the device, either bw (black and white) or color (for color printing)
         * REQUIRE(this->properlyInitialized(), "Device not initialized when calling getType()")
         */

        std::string getType() const;




        /**
         * Overload of the = constructor for jobs since it seems to be needed for something
         * @param inJob
         * @return
         */

        Job& operator=(Job const & inJob);


        /**
         * Overload of the == operator for tests
         * @param d
         * @return
         */
        bool operator == (const Job &J){
            if (jobNr == J.jobNr && pageCount == J.pageCount && type == J.type){
                return true;
            }
            return false;
        }

    private:
        int jobNr, pageCount;
        std::string userName;
        Job *_initCheck;
        std::string type;

        bool properlyInitialized() const;
        System::Device * ownerDevice = nullptr;



    };

} // System

#endif //PROJSOFTENG_JOB_H
