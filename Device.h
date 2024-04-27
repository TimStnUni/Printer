//
// Created by tim on 18/04/24.
//

#ifndef PROJSOFTENG_DEVICE_H
#define PROJSOFTENG_DEVICE_H

#include "DesignByContract.h"
#include <iostream>
#include <string>
#include <vector>



namespace System {

    class Job;
    class PrinterSystem;

    class Device {

        friend class PrinterSystem;
        friend class Job;

    public:

        Device * getInitCheck();

        /**
         * \brief Default Constructor
         */
        Device();

        /**
         * \brief Usual constructor for a printer device
         * @param name : Name of the printer as a string
         * @param emissions : Emissions of the printer in g/page
         * @param speed : Speed of the printer in p/minute
         * ENSURE(this->properlyInitialized(), "Device is not properly initialized");
         */
        Device(std::string name, int emissions, int speed, std::string type, float cost);
//float cost

        /**
         * \brief Copy Constructor that should fix the _initCheck to this
         * @param inDevice device to be copied
         */
        Device(const Device &inDevice);


        /**
         * \brief Setter function for the name of a device
         * @param inName string name of device
         * REQUIRE(!inName.emtpy(), "name should not be empty")
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
         * ENSURE(this->getSpeed() == speed_in, "Speed wasn't correctly set")
         */

        void setSpeed(int &speed_in);

        /**
         * \brief a getter function for the printer speed
         * @return speed in pages/minute
         * REQUIRE(this->properlyInitialized(), "Device not initialized when calling getSpeed()")
         */
        int getSpeed() const;

        //TODO:: filled it in, has to get checked
        /**
         * \brief A setter function for the printer speed
         * @param type_in
         * REQUIRE(!type_in.empty(), "Type shouldn't be empty")
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
         * \brief overloaded equality operator for getters
         * @param d device to be compared
         * @return boolean true or false
         */


        std::vector<Job*> getJobs();

        void addJob(PrinterSystem * ownSystem);

        bool operator == (const Device &d){
            if (name == d.name && emissions == d.emissions && speed == d.speed){
                return true;
            }
            return false;
        }



        Device& operator=(Device const & inDevice);


        Device *_initCheck;
    protected:
        std::string name;
        int emissions, speed;
        std::string type;
        float cost;

        void updatePointer(Job * inPointer, const Job * prevPointer);

        void removeJob(unsigned int jobnr);

        std::vector<System::Job *> jobPtrList;

        bool properlyInitialized() const;


    };


} // System

#endif //PROJSOFTENG_DEVICE_H
