#ifndef __SIMULATION_STRATEGY
#define __SIMULATION_STRATEGY

#include <unordered_map>
#include <string>
#include "BaseConstants.hpp"

// Description: Abstract interface for simulation strategies.
class SimulationStrategy {
    
public:
    virtual ~SimulationStrategy() = default;

    virtual void run() = 0;

protected:
    
};

#endif // __SIMULATION_STRATEGY
