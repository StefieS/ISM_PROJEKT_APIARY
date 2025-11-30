#include "../../../inc/simlib_components/BaseComponents.hpp"
#include <algorithm>

bool TransportGetter::transportAvailableForLoad(Location location) {
    return (this->location == location) && (status == TransportStatus::ReadyToLoad);
}

bool TransportGetter::transportAvailableForUnload(Location location) {
    return (this->location == location) && (status == TransportStatus::ReadyToUnload);
}

bool TransportGetter::transportWaitingForTransport(Location location) {
    return (this->location == location) && (status == TransportStatus::WaitingForTransport);
}
 
void TransportGetter::loadIntoTransport(Entity* caller) {
    vprint("Enter in TransportGetter", LogColor::Default);
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

void TransportGetter::unloadFromTransport() {
    vprint("Leave in TransportGetter", LogColor::Default);
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

void TransportGetter::moveToLocation(Location l) {
    location = l;
    status = TransportStatus::ReadyToUnload;
}

