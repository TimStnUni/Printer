//
// Created by stand on 13/06/2024.
//

#include "CPrinter.h"

namespace System {
    CPrinter::CPrinter(std::string &name_in, int &emissions_in, int &speed_in, float &cost_in) {
        REQUIRE(emissions_in > 0, "Emissions should be positive");
        REQUIRE(speed_in > 0, "Speed should be positive");
        REQUIRE(cost_in>0, "Cost should be positive");
        REQUIRE(!(name_in.empty()), "name shouldn't be empty");

        this->_initCheck = this;



        this->setNameDev(name_in);
        this->setEmissions(emissions_in);
        this->setSpeed(speed_in);
        std::string type = "color";
        this->setType(type);
        this->setCost(cost_in);


        ENSURE(this->properlyInitialized(), "Colour printer is not properly initialized");


    }

    bool CPrinter::isBelowLimit() {

        REQUIRE(properlyInitialized(), "CPrinter wasn't properly initialized");

        if(this->getEmissions() <= limit) {
            return true;
        }
        return false;
    }
} // System