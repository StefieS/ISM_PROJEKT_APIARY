#ifndef __ON_SITE_EXTRACTION_STRATEGY
#define __ON_SITE_EXTRACTION_STRATEGY

#include "SimulationStrategy.hpp"
#include "../constants/OnSiteConstants.hpp"
#include "../simlib_components/OnSiteComponents.hpp"
#include "../utils.hpp"
class OnSiteExtractionStrategy : public SimulationStrategy {

public:

    void run() override;

};

#endif // __ON_SITE_EXTRACTION_STRATEGY