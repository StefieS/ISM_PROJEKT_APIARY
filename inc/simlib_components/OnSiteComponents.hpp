#ifndef __ON_SITE_COMPONENTS
#define __ON_SITE_COMPONENTS

#include <simlib.h>
#include "BaseComponents.hpp"

class OneTrolleyGetter : public ITransportGetter {

public:
    OneTrolleyGetter(int capacity)
        : Trolley("Trolley", capacity),
          location(Location::Hives),
          status(TransportStatus::ReadyToLoad) {}

    bool transportAvailableForLoad(Location location) override;
    bool transportAvailableForUnload(Location location) override;

    void loadIntoTransport(Entity* caller) override;
    void unloadFromTransport() override;

    void moveToLocation(Location l) override;

private:
    Store Trolley;
    Location location;
    TransportStatus status;
};

#endif // __ON_SITE_COMPONENTS