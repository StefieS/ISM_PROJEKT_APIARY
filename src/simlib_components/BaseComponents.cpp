#include "../../inc/simlib_components/BaseComponents.hpp"
#include "../../inc/constants/BaseConstants.hpp"
#include "../../inc/utils.hpp"
using namespace BaseConstants;

// p 3
void UnloadExtractor::Behavior() {

}

// p 2
void LoadingFromShelfToExtractor::Behavior() {

}

// p 0
void GetAndLoadUncappedFrames::Behavior() {

}



void ExtractorRunning::Behavior() {
    while (true) {
        Passivate();
        vprint("ExtractorRunning activated");
        again:
        Wait(TIME_OF_EXTRACTOR_RUNNING);
        vprint("Extractor finished running");
        if (Random() <= PERC_EXTRACTOR_AGAIN) {
            vprint("Extractor started again");
            goto again;
        }

        // signal unloading possible
        
    }
}



void ReturningEmptyFramesToHive::Behavior() {
    while (true) {
        if (!Transport->transportAvailableForUnload(Location::Hives)) {
            Passivate(); // wait until transport comes back from shed
            continue;
        }
    
        vprint("ReturningEmptyFramesToHive activated");
        for (int i = 0; i < framesToReturn; ++i) {
            Seize(*hiveBeekeeper, 3);
            vprint("Returning empty frame " + std::to_string(i + 1) + " of " + std::to_string(framesToReturn));
            Wait(Normal(TIME_TO_PUT_THE_FRAME_BACK, 2));
            Transport->unloadFromTransport();
            Release(*hiveBeekeeper);
            vprint("Returned empty frame " + std::to_string(i + 1));
        }
        vprint("ReturningEmptyFramesToHive completed");
    }
}

void LoadingFromStandToTransport::Behavior() {

    while (true) {
        if (stand == 0 || !Transport->transportAvailableForLoad(Location::Hives)) {
            Passivate(); // wait until there is something on the stand and transport is available
            continue;
        }

        vprint("LoadingFromStandToTransport activated");
        Seize(*hiveBeekeeper, 2);
        vprint("LoadingFromStandToTransport started");
        Wait(Uniform(TIME_FROM_STAND_TO_TRANSPORT - 5, TIME_FROM_STAND_TO_TRANSPORT + 5));

        stand--;
        Transport->loadIntoTransport(this);

        vprint("LoadingFromStandToTransport completed");
        Release(*hiveBeekeeper);
    }
}

void TakingOutFrames::Behavior() {
    vprint("TakingOutFrames activated");
    for (int i = 0; i < FRAMES_PER_HIVE; ++i) {
        Seize(*hiveBeekeeper, 1);
        vprint("Taking out frame " + std::to_string(i + 1) + " of " + std::to_string(FRAMES_PER_HIVE));
        Wait(Normal(TIME_TO_TAKE_OUT_FRAME, 1));
        vprint("Took out frame " + std::to_string(i + 1));

        if (Transport->transportAvailableForLoad(Location::Hives)) {
            Transport->loadIntoTransport(this);
            vprint("Loaded frame into transport");
        } else {

            stand++;

            // LoadingFromStandToTransport activate
            processMap["LoadingFromStandToTransport"]->Activate();
            vprint("No transport available, placing frame on stand");

        }

        Release(*hiveBeekeeper);
    }
    vprint("TakingOutFrames completed");
}

void OpeningHive::Behavior() {
    vprint("OpeningHive activated");
    Seize(*hiveBeekeeper, 0);
    vprint("OpeningHive started");
    Wait(Uniform(TIME_TO_OPEN_HIVE - 5, TIME_TO_OPEN_HIVE + 5));
    new TakingOutFrames();
    Release(*hiveBeekeeper);
    vprint("OpeningHive completed");
}