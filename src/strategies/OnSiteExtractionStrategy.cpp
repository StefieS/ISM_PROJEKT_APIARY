#include "../../inc/strategies/OnSiteExtractionStrategy.hpp"
void OnSiteExtractionStrategy::run() {
    RandomSeed(time(NULL));

    Init(0, 10*60*60); // 3 hour simulation
    
    g_transport = std::make_unique<TransportGetter>(OnSiteConstants::TRANSPORT_CAPACITY);

    hiveBeekeeper = std::make_unique<Facility>("On hivesBeekeeper");
    shedBeekeeper = new Facility("On shedBeekeeper");

    extractor = std::make_unique<Extractor>(BaseConstants::EXTRACTOR_CAPACITY);

    transportBeekeeperAtHives = std::make_unique<Facility>("Transport beekeeper at hives");
    if (separateTranportWorker) {
        transportBeekeeperAtShed = new Facility("Transport beekeeper at shed");
    } else {
        transportBeekeeperAtShed = shedBeekeeper;  // Same person
    }
    transportProcess = std::make_unique<TransportingFrames>(Location::Hives, 
        OnSiteConstants::TRANSPORT_TIME);

    hivesTimer =std::make_unique<Timer>(OnSiteConstants::HIVES_TIMEOUT_TIME, 0);
    shedTimer = std::make_unique<Timer>(OnSiteConstants::SHED_TIMEOUT_TIME, 1);

    BEEHIVES_PROCESSES();
    Run();
}
