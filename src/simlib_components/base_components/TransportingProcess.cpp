#include "../../../inc/simlib_components/BaseComponents.hpp"
#include "../../../inc/constants/BaseConstants.hpp"
#include <algorithm>

void TransportingFrames::Behavior() {
    if (this->location == Location::Hives) {
        // todo correct priority
        Seize(*transportBeekeeperAtShed); // he starts at hives, make unavailable at shed
        vprint("Transporter starting at Hives, seizing transporter beekeeper at shed", LogColor::TransportColor);
    } else {
        Seize(*transportBeekeeperAtHives);
        vprint("Transporter starting at Shed, seizing transporter beekeeper at hives", LogColor::TransportColor);
    }

    while (true) {
        if (!g_transport->transportWaitingForTransport(this->location)) {
            vprint("No transport waiting at location, passivating transporter", LogColor::TransportColor);
            Passivate();
            continue;
        }

        Location next;
        vprint(std::to_string((int)this->location) +" Transporter going with " + std::to_string(g_transport->numberOfFramesInTransport()), LogColor::TransportColor);

        if (this->location == Location::Hives) {
            // todo correct priority
            hivesTimer->setRestart(false);
            hivesTimer->setStop(true);
            Seize(*transportBeekeeperAtHives);
            vprint("Transporter seizing hives beekeeper", LogColor::TransportColor);
            next = Location::Shed;

        } else {
            shedTimer->setRestart(false);
            shedTimer->setStop(true);
            Seize(*transportBeekeeperAtShed);
            vprint("Transporter seizing shed beekeeper", LogColor::TransportColor);
            next = Location::Hives;            
        }
        vprint("Transporter moving to next location", LogColor::TransportColor);
        g_transport->moveToLocation(next);
        Wait(Normal(transportTime, 10));
        
        this->location = next;
        vprint("Transporter arrived at location", LogColor::TransportColor);

        if (this->location == Location::Hives) {
            if (g_transport->numberOfFramesInTransport() == 0) {
                vprint("No frames in transport to unload in hives", LogColor::TransportColor);
                g_transport->setStatus(TransportStatus::ReadyToLoad);
                hivesTimer->setRestart(true);
                hivesTimer->setStop(false);

                hivesTimer->Activate();
                Wait(0.01);
                for (int i = 0; i < std::min(g_transport->capacity(), stand); i++) {
                        new LoadingFromStandToTransport();
                }
            }
            for (int i = 0; i < g_transport->numberOfFramesInTransport(); i++) {
                new ReturningEmptyFramesToHive();
            }
            hivesTimer->setStop(false);
        } else {
                Wait(0.01);

            if (g_transport->numberOfFramesInTransport() == 0) {
                vprint("No frames in transport to unload in shed", LogColor::TransportColor);
                g_transport->setStatus(TransportStatus::ReadyToLoad);
                        Wait(0.01);
             if (g_transport->transportAvailableForLoad(Location::Shed)) {
                    shedTimer->setRestart(true);
                    shedTimer->setStop(false);
                    shedTimer->Activate();
                    for (int i = 0; i < std::min(emptyShelf, g_transport->capacity()); i++) {
                        new FromShelfToTransport();
                    }
                }
            }
            vprint("Numebr of frames in transport: " + std::to_string(g_transport->numberOfFramesInTransport()), LogColor::TransportColor);
            for (int i = 0; i < g_transport->numberOfFramesInTransport(); i++) {
                new GetAndLoadUncappedFrames();
            }
            shedTimer->setStop(false);
        }

        if (this->location == Location::Hives) {
            // todo correct priority
            vprint("Transporter releasing hives beekeeper", LogColor::TransportColor);
            Release(*transportBeekeeperAtHives);
        } else {
            vprint("Transporter releasing shed beekeeper", LogColor::TransportColor);
            Release(*transportBeekeeperAtShed);
        }
        
    }

}

void Timer::Behavior() {
    Stop:
    Passivate();
    Restart:
    Wait(time);

    if (restart) {
        this->restart = false;
        vprint(std::to_string(this->id) + " Timer restarting");
        goto Restart;
    }

    if (stop) {
        vprint(std::to_string(this->id) + " Timer stopping");
        goto Stop;
    }

    vprint(std::to_string(this->id) + " Timer activating transport process");
    g_transport->setStatus(TransportStatus::WaitingForTransport);
    transportProcess->Activate();
    goto Restart;

}

void Timer::setStop(bool to) {
    this->stop = to;
}

void Timer::setRestart(bool to) {
    this->restart = to;
}