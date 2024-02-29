//
// Created by tim on 29/02/24.
//

#include "Printer.h"

namespace Printer {
    Device::Device(std::string name_in, int emissions_in, int speed_in) {

        REQUIRE(emissions_in > 0, "Emissions should be positive");
        REQUIRE(speed_in > 0, "Speed should be positive");

        name = name_in;
        emissions = emissions_in;
        speed = speed_in;


        //TOdo : implement properlyinitialized
        //ENSURE(this->properlyInitialized, "inti");
    }
} // Printer