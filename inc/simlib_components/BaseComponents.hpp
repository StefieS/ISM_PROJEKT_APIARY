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
#include "../utils.hpp"


inline std::unique_ptr<Extractor> extractor = std::make_unique<Extractor>(BaseConstants::EXTRACTOR_CAPACITY);;

inline std::unique_ptr<Facility> hiveBeekeeper = std::make_unique<Facility>("hivesBeekeeper");;
inline Facility* shedBeekeeper = new Facility("On shedBeekeeper");;

inline std::unique_ptr<Facility> transportBeekeeperAtHives = std::make_unique<Facility>("Transport beekeeper at hives");;
inline Facility* transportBeekeeperAtShed;

inline std::unique_ptr<TransportGetter> g_transport;
inline std::unique_ptr<Process> transportProcess;
inline std::unique_ptr<Timer> hivesTimer;
inline std::unique_ptr<Timer> shedTimer;

inline int stand = 0;
inline int shelf = 0;
inline int emptyShelf = 0;

inline uint extractedHoney = 0;

inline uint returnedFrames = 0;

#endif // __BASE_COMPONENTS
