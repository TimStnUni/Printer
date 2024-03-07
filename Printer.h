//
// Created by tim on 29/02/24.
//

#ifndef PROJSOFTENG_PRINTER_H
#define PROJSOFTENG_PRINTER_H

#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include "DesignByContract.h"

//TestComment2


namespace Printer {


    class Device {
    public:
        Device(std::string name, int emissions, int speed);


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
        //I think potentially the layout of this class


        Printer();


    private:
        std::vector<Device> deviceList;
        std::vector<Job> jobList;
        std::unordered_set<unsigned int> jobNrSet;

    };

    class PrinterSystem {

    public:
        //Should simply always be running, no input in constructor.
        PrinterSystem();


    private:
        std::vector<Printer> printerList;

        //Naming is the same as for printer.
        //Potentially this should be replaced by a map that maps a jobnr to a pointer to the job, or at least to some
        //way of identifying which job it belongs to. Right now its own index in the unordered set is also the index of the
        //printer list. This won't work, since there can be multiple jobs within a Printer container.
        //This should probably be a map of jobNr's that map to either indices or pointers to printers in the printerList.
        //Within those there can be a set that simply uses its own index to point to the correct job.
        std::unordered_set<unsigned int> jobNrSet;



        /*If replaced by the following it could probably be implemented as something like
        this->addprinter(printer){
            printerlist.push_back(printer)
            int printerindex = printerlist.size() - 1;

            std::unordered_set<unsigned int> printernrs = printer.getPrinterNrs();

            for (printernrs.size, iterate over printernrs (should probably be done with iterators, but those are a bit finnicky)){
                jobNrMap.add({printernrs.at(i), printerindex});
                }
        }


        this way if later some jobrn needs to be fetched it's a case of

         getJob(jobnr){
            printerlist.at(jobNrMap.at(jobnr)).getJob(jobnr){
                //Some relevant code to be implemented in the printer class, don't know what they would want



        */
        //std::unordered_map<unsigned int, unsigned int> jobNrMap;

    };

} // Printer

#endif //PROJSOFTENG_PRINTER_H
