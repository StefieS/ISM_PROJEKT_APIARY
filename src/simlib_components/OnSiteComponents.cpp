#include "../../inc/simlib_components/OnSiteComponents.hpp"
#include <algorithm>
bool OneTrolleyGetter::transportAvailableForLoad(Location location) {
    return (this->location == location) && (status == TransportStatus::ReadyToLoad);
}

bool OneTrolleyGetter::transportAvailableForUnload(Location location) {
    return (this->location == location) && (status == TransportStatus::ReadyToUnload);
}

bool OneTrolleyGetter::transportWaitingForTransport(Location location) {
    return (this->location == location) && (status == TransportStatus::WaitingForTransport);
}
 
void OneTrolleyGetter::loadIntoTransport(Entity* caller) {
    vprint("Enter in onetrolleygetter", LogColor::Default);
    Trolley.Enter(caller, 1);

    if (this->Trolley.Full()) {
        status = TransportStatus::WaitingForTransport;
        transportProcess->Activate();
    }

    if (this->getLocation() == Location::Hives) {
        hivesTimer->setRestart(true);
        hivesTimer->Activate();
    } else {
        shedTimer->setRestart(true);
        shedTimer->Activate();
    }

}

void OneTrolleyGetter::unloadFromTransport() {
    vprint("Leave in onetrolleygetter", LogColor::Default);
    Trolley.Leave(1);
    if (this->Trolley.Empty()) {
        vprint("Trolley empty after unload", LogColor::Default);
        status = TransportStatus::ReadyToLoad;
        if (this->location == Location::Hives) {
            hivesTimer->setRestart(true);
            hivesTimer->setStop(false);

            hivesTimer->Activate();
            for (int i = 0; i < std::min(g_transport->capacity(), stand); i++) {
                    new LoadingFromStandToTransport();
            }
        } else if (g_transport->transportAvailableForLoad(Location::Shed)) {
            for (int i = 0; i < std::min(emptyShelf, g_transport->capacity()); i++) {
                new FromShelfToTransport();
            }
        }
    }
            vprint("Trolley not empty after unload", LogColor::Default);

}

void OneTrolleyGetter::moveToLocation(Location l) {
    location = l;
    status = TransportStatus::ReadyToUnload;
}

