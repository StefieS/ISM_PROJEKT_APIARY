#ifndef __OFF_SITE_EXTRACTION_STRATEGY
#define __OFF_SITE_EXTRACTION_STRATEGY

#include "SimulationStrategy.hpp"
#include "OffSiteConstants.hpp"

class OffSiteExtractionStrategy : public SimulationStrategy {

public:
    void run() override;

};

#endif // __OFF_SITE_EXTRACTION_STRATEGY