#ifndef __ON_SITE_EXTRACTION_STRATEGY
#define __ON_SITE_EXTRACTION_STRATEGY

#include "SimulationStrategy.hpp"
#include "../constants/OnSiteConstants.hpp"

class OnSiteExtractionStrategy : public SimulationStrategy {

public:
    OnSiteExtractionStrategy(bool separateTranportWorker)
        : separateTranportWorker(separateTranportWorker) {}

    void run() override;
    void onBucketReady() override;


private:
    bool separateTranportWorker;
};

#endif // __ON_SITE_EXTRACTION_STRATEGY