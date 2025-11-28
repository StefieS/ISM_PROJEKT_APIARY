#include "../../../inc/simlib_components/BaseComponents.hpp"
#include "../../../inc/constants/BaseConstants.hpp"
#include "../../../inc/utils.hpp"

using namespace BaseConstants;

void ReturningEmptyFramesToHive::Behavior() {
        vprint("ReturningEmptyFramesToHive activated", LogColor::Hives);
        Seize(*hiveBeekeeper, 3);
        Wait(Normal(TIME_TO_PUT_THE_FRAME_BACK, 2));
        vprint("Returned one frame to hive", LogColor::Hives);
        Transport->unloadFromTransport();
        Release(*hiveBeekeeper);
        vprint("ReturningEmptyFramesToHive completed", LogColor::Hives);
}

void LoadingFromStandToTransport::Behavior() {
        // TODO: spawn when hives available to load and stand != 0
        vprint("LoadingFromStandToTransport activated", LogColor::Hives);
        Seize(*hiveBeekeeper, 2);
        vprint("LoadingFromStandToTransport started", LogColor::Hives);
        Wait(Uniform(TIME_FROM_STAND_TO_TRANSPORT - 5, TIME_FROM_STAND_TO_TRANSPORT + 5));

        stand--;
        Transport->loadIntoTransport(this);

        vprint("LoadingFromStandToTransport completed", LogColor::Hives);
        Release(*hiveBeekeeper);
        if (stand && 
            Transport->transportAvailableForLoad(Location::Hives)) {
                new LoadingFromStandToTransport();
            }
}

void TakingOutFrames::Behavior() {
    vprint("TakingOutFrames activated", LogColor::Hives);
    for (int i = 0; i < FRAMES_PER_HIVE; ++i) {
        Seize(*hiveBeekeeper, 1);
        vprint("Taking out frame " + std::to_string(i + 1) + " of " + std::to_string(FRAMES_PER_HIVE), LogColor::Hives);
        Wait(Normal(TIME_TO_TAKE_OUT_FRAME, 1));
        vprint("Took out frame " + std::to_string(i + 1), LogColor::Hives);

        if (Transport->transportAvailableForLoad(Location::Hives)) {
            Transport->loadIntoTransport(this);
            vprint("Loaded frame into transport", LogColor::Hives);
        } else {

            stand++;

            // LoadingFromStandToTransport activate
            if (Transport->transportAvailableForLoad(Location::Hives)) {
                new LoadingFromStandToTransport();
            }
            vprint("No transport available, placing frame on stand", LogColor::Hives);
        }

        Release(*hiveBeekeeper);
    }
    vprint("TakingOutFrames completed", LogColor::Hives);
}

void OpeningHive::Behavior() {
    vprint("OpeningHive activated", LogColor::Hives);
    Seize(*hiveBeekeeper);
    vprint("OpeningHive started", LogColor::Hives);
    Wait(Uniform(TIME_TO_OPEN_HIVE - 5, TIME_TO_OPEN_HIVE + 5));
    new TakingOutFrames();
    Release(*hiveBeekeeper);
    vprint("OpeningHive completed", LogColor::Hives);
}