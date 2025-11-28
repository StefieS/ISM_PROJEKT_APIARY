#include "../../inc/simlib_components/OnSiteComponents.hpp"

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
    Trolley.Leave(1);
    if (this->Trolley.Empty()) {
        status = TransportStatus::ReadyToLoad;
        if (this->location == Location::Hives) {
            hivesTimer->setRestart(true);
            hivesTimer->setStop(false);

            hivesTimer->Activate();
    
            if (stand && 
                g_transport->transportAvailableForLoad(Location::Hives)) {
                    new LoadingFromStandToTransport();
            }
        } else if (!extractor->isExtractorFree() &&
                    g_transport->transportAvailableForLoad(Location::Shed) && !extractor->isRunning())
                {
                    shedTimer->setRestart(true);
                    shedTimer->setStop(false);
                    shedTimer->Activate();
                    new UnloadExtractor();
                }
    }
}

void OneTrolleyGetter::moveToLocation(Location l) {
    location = l;
    status = TransportStatus::ReadyToUnload;
}

