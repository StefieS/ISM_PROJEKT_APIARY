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
    // todo: activate timer 
    // wait (T);
    // if (something) transportProcess->Activate();
    // nechceme aby sa to aktivovalo ked to uz bolo aktivovane taze staci asi bool activated ?
    // => if (!actived) transportProcess->Activate();
    // za mna dava zmysel

}

void OneTrolleyGetter::unloadFromTransport() {
    Trolley.Leave(1);
    if (this->Trolley.Empty()) {
        status = TransportStatus::ReadyToLoad;
        if (this->location == Location::Hives) {
            if (stand && 
                Transport->transportAvailableForLoad(Location::Hives)) {
                    new LoadingFromStandToTransport();
            }
        } else if (!extractor->isExtractorFree() &&
                    Transport->transportAvailableForLoad(Location::Shed) && !extractor->isRunning())
                {
                    new UnloadExtractor();
                }
    }
}

void OneTrolleyGetter::moveToLocation(Location l) {
    location = l;
    status = TransportStatus::ReadyToUnload;
}
