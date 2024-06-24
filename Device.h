//
// Created by tim on 18/04/24.
//

#ifndef PROJSOFTENG_DEVICE_H
#define PROJSOFTENG_DEVICE_H

#include "DesignByContract.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <queue>

#include "Logger.h"


namespace System {

    class Job;

    class PrinterSystem;

    class Device {

    public:


        /**
         * \brief Default Constructor
         * ENSURE(this->properlyInitialized(), "device was not properly initialized in the default constructor")
         */
        Device();

        /**
         * \brief Usual constructor for a generic printer device
         * @param name : Name of the printer as a string
         * @param emissions : Emissions of the printer in g/page
         * @param speed : Speed of the printer in p/minute
         * @param cost : cost per page in c/page
         * @param type : Type of the printer: Deprecated since introduction of inheritance
         * REQUIRE(emissions_in > 0, "Emissions should be positive");
         *REQUIRE(speed_in > 0, "Speed should be positive");
         *REQUIRE(!type_in.empty(), "type should not be blank");
         *REQUIRE(cost_in>0, "Cost should be positive");
         * REQUIRE(!(name_in.empty()), "name shouldn't be empty")
         * ENSURE(this->properlyInitialized(), "Device is not properly initialized");
         */
        Device(std::string name, int emissions, int speed, std::string type, float cost);


        /**
         * \brief Copy Constructor that should fix the _initCheck to this
         * @param inDevice device to be copied
         * ENSURE(this->properlyInitialized(), "Device not properly initialized in copy constructor")
         */
        Device(const Device &inDevice);


        /**
         * \brief Setter function for the name of a device
         * @param inName string name of device
         * REQUIRE(!inName.emtpy(), "name should not be empty")
         * REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to set name")
         * ENSURE(getNameDev() == inName, "name was not correctly set")
         */
        void setNameDev(std::string &inName);

        /**
         * \brief A getter function for the printer name
         * @return : returns the name of the printer
         * REQUIRE(this->properlyInitialized(), "Device not initialized when calling getNameDev()");
         */
        std::string getNameDev() const;


        /**
         * \brief A setter function for the printer emissions
         * @param emissions_in
         * REQUIRE(emissions_in>0, "emissions should be positive")
         * REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to set emissions")
         * ENSURE(this->getEmissions == emissions_in, "Emissions not correctly set")
         */

        void setEmissions(int &emissions_in);

        /**
         * \brief a getter function for the printer emissions
         * @return emissions of the printer in g/page
         * REQUIRE(this->properlyInitialized(), "Device not initialized when calling getEmissions()");
         */
        int getEmissions() const;


        /**
         * \brief A setter function for the printer speed
         * @param speed_in
         * REQUIRE(speed_in > 0, "Speed should be positive")
         * REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to set speed")
         * ENSURE(this->getSpeed() == speed_in, "Speed wasn't correctly set")
         */

        void setSpeed(int &speed_in);

        /**
         * \brief a getter function for the printer speed
         * @return speed in pages/minute
         * REQUIRE(this->properlyInitialized(), "Device not initialized when calling getSpeed()")
         */
        int getSpeed() const;


        /**
         * \brief A setter function for the printer speed
         * @param type_in
         * REQUIRE(!type_in.empty(), "Type shouldn't be empty")
         * REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to set type")
         * ENSURE(this->getType() == type_in, "Type not correctly set")
         */

        void setType(std::string &type_in);

        /**
         * \brief a getter function for the device type
         * @return returns the type of the device, either bw (black and white) or color (for color printing)
         * REQUIRE(this->properlyInitialized(), "Device not initialized when calling getType()")
         */

        std::string getType() const;

        /**
         * \brief A setter function for the cost of printing
         * @param cost_in
         * REQUIRE(cost_in >= 0, "Cost should be positive")
         * REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to set cost")
         * ENSURE(this->getCost() == cost_in, "Cost not correctly set")
         */

        void setCost(float &cost_in);

        /**
         * \brief a getter function for the printing cost
         * @return euro cents (= 1/100 euros)
         * REQUIRE(this->properlyInitialized(), "Device not initialized when calling getCost()")
         */

        float getCost() const;


        /**
         * \brief getter function for the total nr of pages in the queue for this printer
         * @return
         * REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to get total pages")
         */
        int getTotalPages();


        /**
         * \brief function to add a job to the queue for this device
         * @param jobIn
         * REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to add job")
         * REQUIRE(jobIn != nullptr, "job should be a valid job")
         * ENSURE(*jobPtrQueue.back() == *jobIn, "Job was not correctly added")
         */
        void addJob(Job *jobIn);


        /**
         * \brief Function to remove the front job from the queue
         * @param jobnr
         * REQUIRE(properlyInitialized(), "Device not properly initialized when attempting to remove a job from queue")
         * REQUIRE(jobptr != nullptr, "job should be a valid job")
         * ENSURE should check that it was actually removed, this is currently not done
         */

        void removeJob();


        /**
         * \brief Function to finish the queue of jobs for this printer
         * REQUIRE(properlyInitialized(), "device was not properly initialized when attepting to finish the queue");
         * ENSURE(jobPtrQueue.empty(), "Not all jobs were correctly printed");
         */

        void printAllJobs();


        /**
         * \brief Function to get a pointer to the joblist. Used for infoprinting and checking if devices are finished
         * @return
         * REQUIRE(this->properlyInitialized(), "Device wasn't properly initialized");
         */
        std::deque<Job *> *getJobs();


        /**
         * Function that prints the job currently first in queue
         * REQUIRE(properlyInitialized(), "printer not properly initialized when calling printcurrentjob");
         * REQUIRE(!jobPtrQueue.empty(), "There should be at least 1 job in the queue");
         * ENSURE(printed, "Job was not correctly printed");
         * @return the co2 emissions of the job
         */

        int printCurrentJob();


        /**
         * Function that prints a certain amount of pages for the job currently first in queue
         * @param pages : amount of pages to be printed
         * REQUIRE(properlyInitialized(), "printer not properly initialized when calling printcurrentjob");
         * REQUIRE(!jobPtrQueue.empty(), "There should be at least 1 job in the queue");
         * ENSURE(printed, "job was not correctly printed");
         * @return
         */

        int printCurrentJobPages(unsigned int pages);

        /**
         * Function to get a pointer to the first job in the queue
         * @return
         * REQUIRE(this->properlyInitialized(), "Device wasn't properly initialized");
         * REQUIRE(!jobPtrQueue.empty(), "There should be a current job");
         */

        Job *getCurrentJob();


        /**
         * Function to check if a device is below its mandated CO2 limit
         * @return
         * REQUIRE(properlyInitialized(), "Device wasn't properly initialized");
         */

        virtual bool isBelowLimit();


        /**
         * Overloaded assingment operator. Currently does not seem to be used
         * @param inDevice
         * @return
         */

        Device &operator=(Device const &inDevice);

        /**
         * \brief overloaded equality operator for getters
         * @param d device to be compared
         * @return boolean true or false
         */
        bool operator==(const Device &d) {
            if (name == d.name && emissions == d.emissions && speed == d.speed && type == d.type) {
                return true;
            }
            return false;
        }


        bool properlyInitialized() const;

    private:
        std::string name;
        int emissions, speed;
        std::string type;
        float cost;
        Device *_initCheck;

        std::deque<System::Job *> jobPtrQueue;

        System::Logger logger;

    };


} // System

#endif //PROJSOFTENG_DEVICE_H
