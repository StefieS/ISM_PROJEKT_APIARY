#include "../../inc/strategies/OnSiteExtractionStrategy.hpp"
void OnSiteExtractionStrategy::run() {
    RandomSeed(time(NULL));

    Init(0, 10*60*60); // 3 hour simulation
    
    g_transport = std::make_unique<TransportGetter>(OnSiteConstants::TRANSPORT_CAPACITY);

    if (separateTranportWorker) {
        transportBeekeeperAtShed = new Facility("Transport beekeeper at shed");
    } else {
        transportBeekeeperAtShed = shedBeekeeper;  // Same person
    }

    transportProcess = std::make_unique<TransportingFrames>(Location::Hives, 
        OnSiteConstants::TRANSPORT_TIME);

    hivesTimer =std::make_unique<Timer>(OnSiteConstants::HIVES_TIMEOUT_TIME, 0);
    shedTimer = std::make_unique<Timer>(OnSiteConstants::SHED_TIMEOUT_TIME, 1);
    this->CleaningTime = OnSiteConstants::CLEANING_TIME;
    currentStrategy = this;
    BEEHIVES_PROCESSES();
    Run();
    //REPORT();
}

void OnSiteExtractionStrategy::onBucketReady() {
    (new StrainingBucketOnSite())->Activate();
}
