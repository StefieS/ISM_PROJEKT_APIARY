#ifndef __ON_SITE_EXTRACTION_STRATEGY
#define __ON_SITE_EXTRACTION_STRATEGY

#include "SimulationStrategy.hpp"

constexpr int ON_TIME_EXAMPLE = 50;
// TODO : fill in all time uses


class OnSiteExtractionStrategy : public SimulationStrategy {

public:

    void run() override;

};

#endif // __ON_SITE_EXTRACTION_STRATEGY