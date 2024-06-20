//
// Created by stand on 13/06/2024.
//

#ifndef PROJSOFTENG_BWPRINTER_H
#define PROJSOFTENG_BWPRINTER_H
#include "Device.h"

namespace System {

    class BWPrinter : public Device{

    public:
        /**
         * \brief Usual constructor for a black and white printer device
         * @param name : Name of the printer as a string
         * @param emissions : Emissions of the printer in g/page
         * @param speed : Speed of the printer in p/minute
         * @param cost : cost per page in c/page
         * REQUIRE(emissions_in > 0, "Emissions should be positive");
         * REQUIRE(speed_in > 0, "Speed should be positive");
         * REQUIRE(cost_in>0, "Cost should be positive");
         * REQUIRE(!(name_in.empty()), "name shouldn't be empty")
         * ENSURE(this->properlyInitialized(), "Device is not properly initialized");
        */
        BWPrinter(std::string &name, int &emissions, int &speed, float &cost);

        bool belowLimit();


    private:
        Device * _initCheck;
        int limit = 8;
    };

} // System

#endif //PROJSOFTENG_BWPRINTER_H
