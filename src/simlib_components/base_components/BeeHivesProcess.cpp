#include "../../../inc/simlib_components/BaseComponents.hpp"
#include "../../../inc/constants/BaseConstants.hpp"
#include "../../../inc/utils.hpp"

using namespace BaseConstants;

void ReturningEmptyFramesToHive::Behavior() {
        vprint("ReturningEmptyFramesToHive activated", LogColor::HivesColor);
        Seize(*hiveBeekeeper, 3);
        Wait(Normal(TIME_TO_PUT_THE_FRAME_BACK, 2));
        vprint("Returned one frame to hive", LogColor::HivesColor);
        g_transport->unloadFromTransport();
        Release(*hiveBeekeeper);
        vprint("ReturningEmptyFramesToHive completed", LogColor::HivesColor);
        returnedFrames++;
        if (returnedFrames == BaseConstants::HIVES_TO_OPEN * BaseConstants::FRAMES_PER_HIVE) {
            vprint("All frames returned, stopping timer");
            hivesTimer->setStop(true);
            hivesTimer->setRestart(false);
            shedTimer->setStop(true);
            shedTimer->setRestart(false);
        }
}

void LoadingFromStandToTransport::Behavior() {
        // TODO: spawn when hives available to load and stand != 0
        vprint("LoadingFromStandToTransport activated", LogColor::HivesColor);
        Seize(*hiveBeekeeper, 2);
        vprint("LoadingFromStandToTransport started", LogColor::HivesColor);
        Wait(Uniform(TIME_FROM_STAND_TO_TRANSPORT - 5, TIME_FROM_STAND_TO_TRANSPORT + 5));

        stand--;
        g_transport->loadIntoTransport(this);

        vprint("LoadingFromStandToTransport completed", LogColor::HivesColor);
        Release(*hiveBeekeeper);
        if (stand && 
            g_transport->transportAvailableForLoad(Location::Hives)) {
                new LoadingFromStandToTransport();
            }
}

void TakingOutFrames::Behavior() {
    vprint("TakingOutFrames activated", LogColor::HivesColor);
    for (int i = 0; i < FRAMES_PER_HIVE; ++i) {
        Seize(*hiveBeekeeper, 1);
        vprint("Taking out frame " + std::to_string(i + 1) + " of " + std::to_string(FRAMES_PER_HIVE), LogColor::HivesColor);
        Wait(Normal(TIME_TO_TAKE_OUT_FRAME, 1));
        vprint("Took out frame " + std::to_string(i + 1), LogColor::HivesColor);

        if (g_transport->transportAvailableForLoad(Location::Hives)) {
            g_transport->loadIntoTransport(this);
            vprint("Loaded frame into transport", LogColor::HivesColor);
        } else {

            stand++;

            // LoadingFromStandToTransport activate
            if (g_transport->transportAvailableForLoad(Location::Hives)) {
                new LoadingFromStandToTransport();
            }
            vprint("No transport available, placing frame on stand", LogColor::HivesColor);
        }

        Release(*hiveBeekeeper);
    }
    vprint("TakingOutFrames completed", LogColor::HivesColor);
}

void OpeningHive::Behavior() {
    vprint("OpeningHive activated", LogColor::HivesColor);
    Seize(*hiveBeekeeper);
    vprint("OpeningHive started", LogColor::HivesColor);
    Wait(Uniform(TIME_TO_OPEN_HIVE - 5, TIME_TO_OPEN_HIVE + 5));
    new TakingOutFrames();
    Release(*hiveBeekeeper);
    vprint("OpeningHive completed", LogColor::HivesColor);
}