#ifndef __SIMULATION_STRATEGY
#define __SIMULATION_STRATEGY

#include <unordered_map>
#include <string>

inline constexpr int HIVES = 40;
inline constexpr int FRAMES_PER_HIVE = 7;


// Description: Abstract interface for simulation strategies.
class SimulationStrategy {
    
public:
    //TODO : CONSTRUCTOR FOR TIME
    virtual ~SimulationStrategy() = default;

    virtual void run() = 0;

protected:
    std::unordered_map<std::string, int> Time;
    // TODO : declare shared strategy methods here 
};

#endif // __SIMULATION_STRATEGY
