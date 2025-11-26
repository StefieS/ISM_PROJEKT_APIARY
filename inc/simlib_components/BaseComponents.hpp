#ifndef __BASE_COMPONENTS
#define __BASE_COMPONENTS

#include <simlib.h>
#include <memory>
#include <unordered_map>

inline int hives_to_open = 40;
class ITransportGetter;
inline std::unique_ptr<ITransportGetter> Transport;
inline std::unique_ptr<Facility> hiveBeekeeper;
inline uint stand;
inline std::unordered_map<std::string, std::unique_ptr<Process>> processMap;

enum class Location {
    Hives,
    Shed
};

enum class TransportStatus {
    ReadyToLoad,
    WaitingForTransport,
    ReadyToUnload
};

class ITransportGetter {
public:
    virtual bool transportAvailableForLoad(Location location) = 0;
    virtual bool transportAvailableForUnload(Location location) = 0;

    virtual void loadIntoTransport(Entity* caller) = 0;
    virtual void unloadFromTransport() = 0;

    virtual void moveToLocation(Location l) = 0;
};

class ReturningEmptyFramesToHive : public Process {
public:
    void Behavior() override;
private:
    // set before the activation, based on the number of empty frames the transport has
    int framesToReturn = 0; 
};

class LoadingFromStandToTransport : public Process {
public:
    void Behavior() override;
};

class TakingOutFrames : public Process {
public:
    void Behavior() override;
    TakingOutFrames() {
        Activate();
    }
};

class OpeningHive : public Process {
public:
    void Behavior() override;
    OpeningHive() {
        Activate();
    }
};




#endif // __BASE_COMPONENTS
