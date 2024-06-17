//
// Created by stand on 17/06/2024.
//

#ifndef PROJSOFTENG_SCANJOB_H
#define PROJSOFTENG_SCANJOB_H

#include "Job.h"

namespace System {

    class ScanJob : public Job {
    public:
        /**
        * \brief Usual constructor for a scanner job
        * @param userName_in Username of the owner of the printing job
        * @param pageCount_in How many pages need to be printed
        * @param jobNr_in JobNr for the job
        *
        *REQUIRE(!userName_in.empty(), "Username shouldn't be empty");
        *REQUIRE(pageCount_in>0, "Pagecount should be positive");
        * ENSURE(this->properlyInitialized(), "Job wasn't properly initialized")
        */
        ScanJob(std::string userName_in, int pageCount_in, int jobNr_in);

    private:
        Job *_initCheck;
    };

} // System

#endif //PROJSOFTENG_SCANJOB_H
