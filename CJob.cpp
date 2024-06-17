//
// Created by stand on 17/06/2024.
//

#include "CJob.h"

namespace System {
    CJob::CJob(std::string userName_in, int pageCount_in, int jobNr_in) {
        REQUIRE(!userName_in.empty(), "Username shouldn't be empty");
        REQUIRE(pageCount_in > 0, "Pagecount should be positive");


        this->_initCheck = this;

        this->setUserName(userName_in);
        this->setPageCount(pageCount_in);
        this->setJobNr(jobNr_in);
        std::string type = "color";
        this->setType(type);


        ENSURE(this->properlyInitialized(), "Job wasn't properly initialized");
    }
} // System