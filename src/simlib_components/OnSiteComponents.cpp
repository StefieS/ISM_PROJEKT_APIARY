#include "../../inc/simlib_components/OnSiteComponents.hpp"
#include <simlib.h>
bool OneTrolleyGetter::transportAvailableForLoad(Location location) {
    return (this->location == location) && (status == TransportStatus::ReadyToLoad);
}

bool OneTrolleyGetter::transportAvailableForUnload(Location location) {
    return (this->location == location) && (status == TransportStatus::ReadyToUnload);
}
 
void OneTrolleyGetter::loadIntoTransport(Entity* caller) {
    Trolley.Enter(caller, 1);
    if (this->Trolley.Full()) {
        status = TransportStatus::WaitingForTransport;
        // todo signal that transport is ready to go
    }
}

void OneTrolleyGetter::unloadFromTransport() {
    Trolley.Leave(1);
    if (this->Trolley.Empty()) {
        status = TransportStatus::ReadyToLoad;
        // todo signal that transport is ready to be loaded
    }
}

void OneTrolleyGetter::moveToLocation(Location l) {
    location = l;
}
