#include "../../inc/strategies/OnSiteExtractionStrategy.hpp"

void OnSiteExtractionStrategy::run() {
    RandomSeed(time(NULL));

    Init(0, 3*60*60); // 3 hour simulation
    
    g_transport = std::make_unique<OneTrolleyGetter>(OnSiteConstants::TRANSPORT_CAPACITY);

    hiveBeekeeper = std::make_unique<Facility>("On hivesBeekeeper");
    shedBeekeeper = std::make_unique<Facility>("On shedBeekeeper");

    extractor = std::make_unique<Extractor>(BaseConstants::EXTRACTOR_CAPACITY);

    transportBeekeeperAtHives = std::make_unique<Facility>("Transport beekeeper at hives");
    transportBeekeeperAtShed = std::make_unique<Facility>("Transport beekeeper at shed");
    transportProcess = std::make_unique<TransportingFrames>(Location::Hives, 
        OnSiteConstants::TRANSPORT_TIME);

    hivesTimer =std::make_unique<Timer>(OnSiteConstants::HIVES_TIMEOUT_TIME);
    shedTimer = std::make_unique<Timer>(OnSiteConstants::SHED_TIMEOUT_TIME);

    BEEHIVES_PROCESSES();
    Run();
}
