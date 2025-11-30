#include "../../inc/strategies/OffSiteExtractionStrategy.hpp"


void OffSiteExtractionStrategy::run() {
    //Transport = std::make_unique<Store>(OffSiteConstants::TRANSPORT_CAPACITY);
    hiveBeekeeper = std::make_unique<Facility>("OFF_hivesBeekeeper");
    shedBeekeeper = new Facility("OFF_shedBeekeeper");
    
}