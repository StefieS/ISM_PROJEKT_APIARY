#include "../../inc/strategies/OnSiteExtractionStrategy.hpp"


void OnSiteExtractionStrategy::run() {
    Transport = std::make_unique<Store>(OnSiteConstants::TRANSPORT_CAPACITY);
    hiveBeekeeper = std::make_unique<Facility>("On beekeeper");
}
