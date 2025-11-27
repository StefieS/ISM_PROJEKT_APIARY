#ifndef __BASE_COMPONENTS
#define __BASE_COMPONENTS

#include <simlib.h>
#include <memory>
#include <unordered_map>
#include "base_components/InterfaceTransport.hpp"
#include "base_components/Extractor.hpp"
#include "base_components/BeeHivesProcess.hpp"
#include "base_components/ExtractorProcess.hpp"

inline int hives_to_open = 40;

inline std::unique_ptr<ITransportGetter> Transport;
inline std::unique_ptr<Extractor> extractor;
inline std::unique_ptr<Facility> hiveBeekeeper;
inline std::unique_ptr<Facility> shedBeekeeper;
inline uint stand;
inline std::unordered_map<std::string, std::unique_ptr<Process>> processMap;


#endif // __BASE_COMPONENTS
