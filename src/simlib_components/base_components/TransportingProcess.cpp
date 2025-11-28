#include "../../../inc/simlib_components/BaseComponents.hpp"
#include "../../../inc/constants/BaseConstants.hpp"


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
            for (int i = 0; i < g_transport->numberOfFramesInTransport(); i++) {
                new ReturningEmptyFramesToHive();
            }
            hivesTimer->setStop(false);
        } else {
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
    if (restart) goto Restart;

    if (stop) goto Stop;

    transportProcess->Activate();
    goto Restart;

}

void Timer::setStop(bool to) {
    this->stop = to;
}

void Timer::setRestart(bool to) {
    this->restart = to;
}