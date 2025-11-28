#ifndef __INTERFACE_TRANSPORT
#define __INTERFACE_TRANSPORT
#include <simlib.h>

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
    virtual bool transportWaitingForTransport(Location location) = 0;

    virtual int numberOfFramesInTransport() = 0;

    virtual void loadIntoTransport(Entity* caller) = 0;
    virtual void unloadFromTransport() = 0;

    virtual void moveToLocation(Location l) = 0;
};

#endif // __INTERFACE_TRANSPORT