#include "../../inc/strategies/OffSiteExtractionStrategy.hpp"


void OffSiteExtractionStrategy::run() {
    RandomSeed(time(NULL));

    Init(0, 10*60*60); // 3 hour simulation
    
    g_transport = std::make_unique<TransportGetter>(OffSiteConstants::TRANSPORT_CAPACITY);

    transportBeekeeperAtShed = shedBeekeeper;
    
    transportProcess = std::make_unique<TransportingFrames>(Location::Hives, 
        OffSiteConstants::TRANSPORT_TIME);

    hivesTimer =std::make_unique<Timer>(OffSiteConstants::HIVES_TIMEOUT_TIME, 0);
    shedTimer = std::make_unique<Timer>(OffSiteConstants::SHED_TIMEOUT_TIME, 1);
    this->CleaningTime = OffSiteConstants::CLEANING_TIME;
    currentStrategy = this;
    BEEHIVES_PROCESSES();
    Run();
    //REPORT();
}

// OffSiteExtractionStrategy.cpp
void OffSiteExtractionStrategy::onBucketReady() {
    // Off-site: start straining immediately
    (new StrainingBucketOffSite())->Activate();
}