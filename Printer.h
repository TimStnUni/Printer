//
// Created by tim on 29/02/24.
//

#ifndef PROJSOFTENG_PRINTER_H
#define PROJSOFTENG_PRINTER_H

#include <string>
#include <vector>
#include <set>

#include "DesignByContract.h"


namespace Printer {


    class Device {
    public:
        Device(std::string  name, int  emissions, int  speed);


    protected:
        std::string name;
        int emissions, speed;



    };


    class Job {

    public:
        Job(std::string userName_in, int pageCount_in, int jobNr_in);


    private:
        int jobNr, pageCount;
        std::string userName;
    };

    class Printer {


    public:
        Printer();




    private:
        std::vector<Device> deviceList;
        std::vector<Job> jobList;
        std::set<unsigned int> jobNrSet;

    };

} // Printer

#endif //PROJSOFTENG_PRINTER_H
