#ifndef __BASE_COMPONENTS
#define __BASE_COMPONENTS

#include <simlib.h>
#include <memory>
#include <unordered_map>
#include "base_components/InterfaceTransport.hpp"
#include "base_components/Extractor.hpp"
#include "base_components/BeeHivesProcess.hpp"
#include "base_components/ExtractorProcess.hpp"
#include "base_components/TransportProcess.hpp"
#include "../utils.hpp"


inline std::unique_ptr<ITransportGetter> g_transport;
inline std::unique_ptr<Extractor> extractor;
inline std::unique_ptr<Facility> hiveBeekeeper;
inline std::unique_ptr<Facility> shedBeekeeper;

inline std::unique_ptr<Facility> transportBeekeeperAtShed;
inline std::unique_ptr<Facility> transportBeekeeperAtHives;

inline std::unique_ptr<Process> transportProcess;
inline std::unique_ptr<Process> hivesTimer;
inline std::unique_ptr<Process> shedTimer;

inline uint stand = 0;
inline uint shelf = 0;


#endif // __BASE_COMPONENTS
