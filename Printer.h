//
// Created by tim on 29/02/24.
//

#ifndef PROJSOFTENG_PRINTER_H
#define PROJSOFTENG_PRINTER_H

#include <string>

#include "DesignByContract.h"


namespace Printer {


    class Device {
    public:
        Device(std::string  name, int  emissions, int  speed);


    protected:
        std::string name;
        int emissions, speed;



    };

    class Printer {

    };

} // Printer

#endif //PROJSOFTENG_PRINTER_H
