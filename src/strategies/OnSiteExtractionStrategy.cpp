#include "../../inc/strategies/OnSiteExtractionStrategy.hpp"

void OnSiteExtractionStrategy::run() {
    Transport = std::make_unique<OneTrolleyGetter>(OnSiteConstants::TRANSPORT_CAPACITY);
    hiveBeekeeper = std::make_unique<Facility>("On beekeeper");
    Init(0, 1*60*60); // 1 hour simulation
    BEEHIVES_PROCESSES();
    Run();
}
