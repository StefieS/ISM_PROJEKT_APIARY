#ifndef __BASE_COMPONENTS
#define __BASE_COMPONENTS

#include <simlib.h>
#include <memory>
#include <unordered_map>

#include "../constants/BaseConstants.hpp"
#include "base_components/TransportGetter.hpp"
#include "base_components/Extractor.hpp"
#include "base_components/BeeHivesProcess.hpp"
#include "base_components/ExtractorProcess.hpp"
#include "base_components/TransportingProcess.hpp"
#include "../strategies/SimulationStrategy.hpp"
#include "../utils.hpp"


inline std::unique_ptr<Extractor> extractor = std::make_unique<Extractor>(BaseConstants::EXTRACTOR_CAPACITY);

inline std::unique_ptr<Facility> hiveBeekeeper = std::make_unique<Facility>("hivesBeekeeper");
inline Facility* shedBeekeeper = new Facility("On shedBeekeeper");

inline std::unique_ptr<Facility> transportBeekeeperAtHives = std::make_unique<Facility>("Transport beekeeper at hives");
inline Facility* transportBeekeeperAtShed;

inline Queue bucketsWaitingToStrain;

inline std::unique_ptr<TransportGetter> g_transport;
inline std::unique_ptr<Process> transportProcess;
inline std::unique_ptr<Timer> hivesTimer;
inline std::unique_ptr<Timer> shedTimer;    

inline int stand = 0;
inline int shelf = 0;
inline int emptyShelf = 0;

inline uint extractedHoney = 0;

inline uint returnedFrames = 0;


inline Stat stat_hiveOpenTime("Hive Open Time");
inline Stat stat_frameRemovalTime("Frame Removal Time");
inline Stat stat_frameToTransportTime("Frame to Transport Time");

inline Stat stat_waitToEnterExtractor("Wait to Enter Extractor");
inline Stat stat_extractorRunningTime("Extractor Running Time");
inline Stat stat_waitToUnloadExtractor("Wait to Unload Extractor");

inline Stat stat_waitHiveBeekeeper("Beekeeper Wait at Hive");
inline Stat stat_waitShedBeekeeper("Beekeeper Wait at Shed");
inline Stat stat_waitTransportBeekeeperHives("Transport Worker Wait at Hives");
inline Stat stat_waitTransportBeekeeperShed("Transport Worker Wait at Shed");

inline Histogram h_transportWaitHives("Transport Wait at Hives", 0, 500, 50);
inline Histogram h_transportWaitShed("Transport Wait at Shed", 0, 500, 50);
#endif // __BASE_COMPONENTS
