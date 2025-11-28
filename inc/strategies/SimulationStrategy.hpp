#ifndef __SIMULATION_STRATEGY
#define __SIMULATION_STRATEGY

#include <unordered_map>
#include <string>
#include "../constants/BaseConstants.hpp"
#include "../simlib_components/BaseComponents.hpp"
#include <memory>
// Description: Abstract interface for simulation strategies.
class SimulationStrategy {
    
public:
    virtual ~SimulationStrategy() = default;

    virtual void run() = 0;
    
};

#define BEEHIVES_PROCESSES() do { \
    transportProcess->Activate(); \
    for (int i = 0; i < BaseConstants::HIVES_TO_OPEN; i++) { \
        new OpeningHive(); \
    } \
} while(0)


#endif // __SIMULATION_STRATEGY
