#include "../../../inc/simlib_components/BaseComponents.hpp"
#include "../../../inc/constants/BaseConstants.hpp"
#include "../../../inc/utils.hpp"

using namespace BaseConstants;

// p 3
void UnloadExtractor::Behavior() {
    vprint("UnloadExtractor activated");
    Seize(*shedBeekeeper, 3);
    vprint("UnloadExtractor started");
    Wait(Uniform(TIME_TO_UNLOAD_FRAME_FROM_EXTRACTOR - 2, TIME_TO_UNLOAD_FRAME_FROM_EXTRACTOR + 2));
    extractor->unloadFromExtractor();
    Transport->loadIntoTransport(this);
    vprint("Unloaded one frame from extractor");
    Release(*shedBeekeeper);
    if (!extractor->isExtractorFree() && !extractor->isRunning() &&
        Transport->transportAvailableForLoad(Location::Shed)) {
        vprint("Spawning new UnloadExtractor process recursively");
        new UnloadExtractor();
    } else if (shelf && extractor->isExtractorFree() && !extractor->isRunning()) {
        new LoadingFromShelfToExtractor();
    }
}

// p 2
void LoadingFromShelfToExtractor::Behavior() {
    // TODO: spawn when extractor available to load and shelf != 0
    vprint("LoadingFromShelfToExtractor activated");
    Seize(*shedBeekeeper, 2);
    vprint("LoadingFromShelfToExtractor started");
    Wait(Uniform(TIME_TO_PUT_FRAME - 2, TIME_TO_PUT_FRAME + 2));

    shelf--;
    extractor->loadIntoExtractor(this);

    vprint("LoadingFromShelfToExtractor completed");
    Release(*shedBeekeeper);
    if (shelf && extractor->isExtractorFree()) {
        new LoadingFromShelfToExtractor();
    }
}

// p 0
void GetAndLoadUncappedFrames::Behavior() {
    Seize(*shedBeekeeper);
    vprint("GetAndLoadUncappedFrames activated");
    Transport->unloadFromTransport();
    if (Random() <= PERC_LONG_UNCAPPING) {
        Wait(Normal(TIME_OF_LONG_UNCAPPING, 10));
    } else {
        Wait(Normal(TIME_OF_SHORT_UNCAPPING, 5));
    }

    Wait(TIME_TO_PUT_FRAME);

    if (extractor->isExtractorFree()) {
        extractor->loadIntoExtractor(this);
        Release(*shedBeekeeper);
    } else {
        shelf++;
        vprint("shelf++");
        Release(*shedBeekeeper);
        if (shelf && extractor->isExtractorFree()) {
            new LoadingFromShelfToExtractor();
        }
    }

}

void ExtractorRunning::Behavior() {
    vprint("ExtractorRunning activated");
    extractor->startRunning();
    again:
    Wait(TIME_OF_EXTRACTOR_RUNNING);
    vprint("Extractor finished running");

    if (Random() <= PERC_EXTRACTOR_AGAIN) {
        vprint("Extractor started again");
        goto again;
    }
    extractor->stopRunning();
    if (Transport->transportAvailableForLoad(Location::Shed) && !extractor->isExtractorFree()) {
        new UnloadExtractor();
    }

    if (shelf && extractor->isExtractorFree()) {
        new LoadingFromShelfToExtractor();
    }
}