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

class TransportGetter {
public:
TransportGetter(int capacity)
        : Trolley("Trolley", capacity),
          location(Location::Hives),
          status(TransportStatus::ReadyToLoad) {}

    bool transportAvailableForLoad(Location location);
    bool transportAvailableForUnload(Location location);
    bool transportWaitingForTransport(Location location);

    int numberOfFramesInTransport() {
        return Trolley.Used();
    }

    int capacity() {
        return Trolley.Capacity();
    }

    void loadIntoTransport(Entity* caller);
    void unloadFromTransport();

    void setStatus(TransportStatus newStatus) {
        status = newStatus;
    }
    void moveToLocation(Location l);

    Location getLocation() {
        return location;
    }

private:
    Store Trolley;
    Location location;
    TransportStatus status;
};


#endif // __INTERFACE_TRANSPORT