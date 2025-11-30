#include "../../../inc/simlib_components/BaseComponents.hpp"
#include "../../../inc/constants/BaseConstants.hpp"
#include "../../../inc/utils.hpp"

using namespace BaseConstants;

void ReturningEmptyFramesToHive::Behavior() {
        Wait(0.01);

        vprint("ReturningEmptyFramesToHive activated", LogColor::HivesColor);
        Seize(*hiveBeekeeper);
        Wait(Normal(TIME_TO_PUT_THE_FRAME_BACK, 2));
        vprint("Returned one frame to hive", LogColor::HivesColor);
        g_transport->unloadFromTransport();
        vprint("ReturningEmptyFramesToHive completed", LogColor::HivesColor);
        returnedFrames++;
            Wait(0.01);
        if (returnedFrames == BaseConstants::HIVES_TO_OPEN * BaseConstants::FRAMES_PER_HIVE) {
            vprint("All frames returned, stopping timer");
            hivesTimer->setStop(true);
            hivesTimer->setRestart(false);
            shedTimer->setStop(true);
            shedTimer->setRestart(false);
        }
        Release(*hiveBeekeeper);

}

void LoadingFromStandToTransport::Behavior() {
        Wait(0.01);

        // TODO: spawn when hives available to load and stand != 0
        vprint("LoadingFromStandToTransport activated", LogColor::HivesColor);
        Seize(*hiveBeekeeper);
        vprint("LoadingFromStandToTransport started", LogColor::HivesColor);
        Wait(Uniform(TIME_FROM_STAND_TO_TRANSPORT - 5, TIME_FROM_STAND_TO_TRANSPORT + 5));

        stand--;
        g_transport->loadIntoTransport(this);
        Wait(0.01);
        vprint("LoadingFromStandToTransport completed", LogColor::HivesColor);
        Release(*hiveBeekeeper);

}

void TakingOutFrames::Behavior() {
        Wait(0.01);

    vprint("TakingOutFrames spawned", LogColor::HivesColor);
    Seize(*hiveBeekeeper);
    vprint("TakingOutFrames started", LogColor::HivesColor);
    Wait(Normal(TIME_TO_TAKE_OUT_FRAME, 1));
    vprint("Took out 1 frame ", LogColor::HivesColor);
        Wait(0.01);

    if (g_transport->transportAvailableForLoad(Location::Hives)) {
        g_transport->loadIntoTransport(this);
        vprint("Loaded frame into transport", LogColor::HivesColor);
    } else {

        stand++;
        vprint("No transport available, placing frame on stand", LogColor::HivesColor);
    }

    Release(*hiveBeekeeper);
    vprint("TakingOutFrames completed", LogColor::HivesColor);
}

void OpeningHive::Behavior() {
    vprint("OpeningHive activated", LogColor::HivesColor);
    Seize(*hiveBeekeeper);
    vprint("OpeningHive started", LogColor::HivesColor);
    Wait(Uniform(TIME_TO_OPEN_HIVE - 5, TIME_TO_OPEN_HIVE + 5));
    vprint("Hive opened", LogColor::HivesColor);
    for (int i = 0; i < FRAMES_PER_HIVE; i++) {
        new TakingOutFrames();
    }
    Wait(0.01);
    Release(*hiveBeekeeper);
    vprint("OpeningHive completed", LogColor::HivesColor);
}