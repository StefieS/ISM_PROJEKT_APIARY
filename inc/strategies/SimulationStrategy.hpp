#ifndef __SIMULATION_STRATEGY
#define __SIMULATION_STRATEGY

#include <unordered_map>
#include <string>
#include "../constants/BaseConstants.hpp"
#include "../simlib_components/BaseComponents.hpp"
#include <memory>
// Description: Abstract interface for simulation strategies.
class SimulationStrategy;
inline SimulationStrategy* currentStrategy;

class SimulationStrategy {
    
public:
    virtual ~SimulationStrategy() = default;
    virtual void onBucketReady() = 0;
    virtual void run() = 0;
    int CleaningTime;
};

#define BEEHIVES_PROCESSES() do { \
    transportProcess->Activate(); \
    for (int i = 0; i < BaseConstants::HIVES_TO_OPEN; i++) { \
        new OpeningHive(); \
    } \
} while(0)

#define REPORT() do { \
    stat_hiveOpenTime.Output(); \
    stat_frameRemovalTime.Output(); \
    stat_frameToTransportTime.Output(); \
    stat_waitToEnterExtractor.Output(); \
    stat_extractorRunningTime.Output(); \
    stat_waitToUnloadExtractor.Output(); \
    h_transportWaitHives.Output(); \
    h_transportWaitShed.Output(); \
} while(0)


#endif // __SIMULATION_STRATEGY
