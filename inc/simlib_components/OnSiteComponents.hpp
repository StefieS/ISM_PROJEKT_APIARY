#ifndef __ON_SITE_COMPONENTS
#define __ON_SITE_COMPONENTS

#include "BaseComponents.hpp"

class OneTrolleyGetter : public ITransportGetter {

public:
    OneTrolleyGetter(int capacity)
        : Trolley("Trolley", capacity),
          location(Location::Hives),
          status(TransportStatus::ReadyToLoad) {}

    bool transportAvailableForLoad(Location location) override;
    bool transportAvailableForUnload(Location location) override;
    bool transportWaitingForTransport(Location location) override;

    int numberOfFramesInTransport() override {
        return Trolley.Used();
    }

    void loadIntoTransport(Entity* caller) override;
    void unloadFromTransport() override;

    void setStatus(TransportStatus newStatus) {
        status = newStatus;
    }
    void moveToLocation(Location l) override;

    Location getLocation() override {
        return location;
    }

private:
    Store Trolley;
    Location location;
    TransportStatus status;
};



#endif // __ON_SITE_COMPONENTS