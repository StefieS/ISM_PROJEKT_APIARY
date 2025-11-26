#include "../../inc/strategies/SimulationStrategy.hpp"


// TODO: Define all shared functions

void SimulationStrategy::beeHivesProcess() {
    for (int i = 0; i < hives_to_open; i++) {
        new OpeningHive();
    }
    
    

}