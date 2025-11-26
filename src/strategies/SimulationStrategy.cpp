#include "../../inc/strategies/SimulationStrategy.hpp"


// TODO: Define all shared functions

void SimulationStrategy::beeHivesProcess() {
    
    for (int i = 0; i < hives_to_open; i++) {
        new OpeningHive();
    }

    processMap["LoadingFromStandToTransport"] = new LoadingFromStandToTransport();
    processMap["ReturningEmptyFramesToHive"] = new ReturningEmptyFramesToHive();
    processMap["LoadingFromStandToTransport"]->activate;
    processMap["ReturningEmptyFramesToHive"]->activate;

}