#include "../../../inc/simlib_components/BaseComponents.hpp"
#include "../../../inc/constants/BaseConstants.hpp"
void TransportingFrames::Behavior() {
    if (this->location == Location::Hives) {
        // todo correct priority
        Seize(*transportBeekeeperAtShed); // he starts at hives, make unavailable at shed
        vprint("Transporter starting at Hives, seizing transporter beekeeper at shed", LogColor::Transport);
    } else {
        Seize(*transportBeekeeperAtHives);
        vprint("Transporter starting at Shed, seizing transporter beekeeper at hives", LogColor::Transport);
    }

    while (true) {
        if (!Transport->transportWaitingForTransport(this->location)) {
            vprint("No transport waiting at location, passivating transporter", LogColor::Transport);
            Passivate();
            continue;
        }

        Location next;

        if (this->location == Location::Hives) {
            // todo correct priority
            Seize(*transportBeekeeperAtHives);
            vprint("Transporter seizing hives beekeeper", LogColor::Transport);
            next = Location::Shed;
        } else {
            Seize(*transportBeekeeperAtShed);
            vprint("Transporter seizing shed beekeeper", LogColor::Transport);
            next = Location::Hives;
        }
        vprint("Transporter moving to next location", LogColor::Transport);
        Wait(Normal(transportTime, 10));
        
        Transport->moveToLocation(next);
        this->location = next;
        vprint("Transporter arrived at location", LogColor::Transport);

        if (this->location == Location::Hives) {
            for (int i = 0; i < Transport->numberOfFramesInTransport(); i++) {
                new ReturningEmptyFramesToHive();
            }
        } else {
            for (int i = 0; i < Transport->numberOfFramesInTransport(); i++) {
                new GetAndLoadUncappedFrames();
            }
        }

        if (this->location == Location::Hives) {
            // todo correct priority
            vprint("Transporter releasing hives beekeeper", LogColor::Transport);
            Release(*transportBeekeeperAtHives);
        } else {
            vprint("Transporter releasing shed beekeeper", LogColor::Transport);
            Release(*transportBeekeeperAtShed);
        }
        
    }

}