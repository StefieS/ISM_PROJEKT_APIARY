#include "../../inc/strategies/OffSiteExtractionStrategy.hpp"


void OffSiteExtractionStrategy::run() {
    RandomSeed(time(NULL));

    Init(0, 10*60*60); // 3 hour simulation
    
    g_transport = std::make_unique<TransportGetter>(OffSiteConstants::TRANSPORT_CAPACITY);

    hiveBeekeeper = std::make_unique<Facility>("Off hivesBeekeeper");
    shedBeekeeper = new Facility("Off shedBeekeeper");

    extractor = std::make_unique<Extractor>(BaseConstants::EXTRACTOR_CAPACITY);

    transportBeekeeperAtHives = std::make_unique<Facility>("Transport beekeeper at hives");
    
    transportBeekeeperAtShed = shedBeekeeper;
    
    transportProcess = std::make_unique<TransportingFrames>(Location::Hives, 
        OffSiteConstants::TRANSPORT_TIME);

    hivesTimer =std::make_unique<Timer>(OffSiteConstants::HIVES_TIMEOUT_TIME, 0);
    shedTimer = std::make_unique<Timer>(OffSiteConstants::SHED_TIMEOUT_TIME, 1);

    BEEHIVES_PROCESSES();
    Run();
    
}