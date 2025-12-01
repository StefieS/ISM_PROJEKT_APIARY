#ifndef __OFF_SITE_EXTRACTION_STRATEGY
#define __OFF_SITE_EXTRACTION_STRATEGY

#include "SimulationStrategy.hpp"
#include "../constants/OffSiteConstants.hpp"

class OffSiteExtractionStrategy : public SimulationStrategy {

public:
    void run() override;
    void onBucketReady() override;

};

#endif // __OFF_SITE_EXTRACTION_STRATEGY