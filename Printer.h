//
// Created by tim on 29/02/24.
//

#ifndef PROJSOFTENG_PRINTER_H
#define PROJSOFTENG_PRINTER_H


#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <fstream>
#include <queue>
#include <fstream>
#include <algorithm>


#include "DesignByContract.h"
#include "tinystr.h"
#include "tinyxml.h"
#include "Device.h"
#include "Job.h"
#include "XMLParser.h"
using namespace std;



namespace System {







    /**
     * \brief Printer class. This contains some devices (can technically be 0, for now no functionality changes) and some jobs
     */

    class Printer {


    public:


        /**
         * \brief Constructor for a printer (not a printer device).
         * ENSURE(this->properlyInitialized(), "Printer was not properly initialized");
         */
        Printer();

        Printer(const Printer &inPrinter);



        //Todo make a version of this function that takes a single device and pushes it back into the devicelist


        /**
         * \brief Function to add a printer device to a printer container
         * @param device_in a vector of devices to be added.
         * REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling addDevices()")
         *
         * //The above ensure is not yet implemented, and wouldn't work with the current implementation anyways
         */
        void addDevices(std::vector<Device> device_in);

        /**
         * \brief Function to add some jobs to a printer
         * @param jobs Double ended queue of jobs.
         * @param jobnrs Unordered set of jobnrs. This is in the process of being reimplemented
         * REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling addJobs()")
         */
        void
        addJobs(std::deque<Job> &jobs, std::map<unsigned int, unsigned int> &jobnrs, std::set<unsigned int> &jobnrSet);




        /**
         * \brief Getter function for a printer device from a printer
         * @param index Index of the device to be gotten
         * @return first device stored in the printer
         * REQUIRE(this->properlyInitialized(), "Printer was not initialized when calling getDevice()")
         * REQUIRE(index > 0 && index < this->devicelist.size(), "Index should be within bounds");
         */
        Device getDevice(int index);

        //TODO: getDeviceList gemaakt om list van devices in bij te houden?
        std::vector<Device> getDeviceList();

        /**
         * \brief Getter for all jobs
         * @return
         */
        std::deque<Job> getJobList();

        /**
         * \brief Getter for all jobnrs. This should be deprecated
         * @return
         */
        std::map<unsigned int, unsigned int> getJobNrMap();

        /**
         * \brief Getter for all jobnrs to add to the large collection of unique jobnrs for the system
         * @return
         */

        std::set<unsigned int> getJobNrSet();

        /**
         * \brief Getter function that returns the index in the JobList of this printer
         * @param jobNr
         * @return
         */

        unsigned int getJobIndex(unsigned int &jobNr);


        /**
         * \brief Housekeeping function that keeps all jobnrs pointing to the correct job
         * @param jobNr
         */
        void removeJob(unsigned int jobNr);

    private:

        Printer *_initCheck;

        bool properlyInitialized();

        std::vector<Device> deviceList;



        //The deque idea was cute but ultimately uneccesary since we never actually loop over it.
        //The entire idea of using sets and maps for duplicate checking is neat, but ultimately should probably not be
        //outside of this. Do I really want to reengineer all the functions? No. Should I? probably.

        //The deque is nice for the looping over all jobs since then it's a simple pop-front or pop-back operation
        //but now it's simply a more complicated joblist.
        std::deque<Job> jobList;
        std::map<unsigned int, unsigned int> jobNrMap;
        std::set<unsigned int> jobNrSet;

    };


} // Printer

#endif //PROJSOFTENG_PRINTER_H
