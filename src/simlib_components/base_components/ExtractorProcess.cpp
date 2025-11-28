#include "../../../inc/simlib_components/BaseComponents.hpp"
#include "../../../inc/constants/BaseConstants.hpp"
#include "../../../inc/utils.hpp"

using namespace BaseConstants;

// p 3
void UnloadExtractor::Behavior() {
    vprint("UnloadExtractor activated", LogColor::ExtractorColor);
    Seize(*shedBeekeeper, 3);
    vprint("UnloadExtractor started", LogColor::ExtractorColor);
    Wait(Uniform(TIME_TO_UNLOAD_FRAME_FROM_EXTRACTOR - 2, TIME_TO_UNLOAD_FRAME_FROM_EXTRACTOR + 2));
    extractor->unloadFromExtractor();
    g_transport->loadIntoTransport(this);
    vprint("Unloaded one frame from extractor", LogColor::ExtractorColor);
    Release(*shedBeekeeper);
    if (!extractor->isExtractorFree() && !extractor->isRunning() &&
        g_transport->transportAvailableForLoad(Location::Shed)) {
        vprint("Spawning new UnloadExtractor process recursively", LogColor::ExtractorColor);
        new UnloadExtractor();
    } else if (shelf && extractor->isExtractorFree() && !extractor->isRunning()) {
        new LoadingFromShelfToExtractor();
    }
}

// p 2
void LoadingFromShelfToExtractor::Behavior() {
    // TODO: spawn when extractor available to load and shelf != 0
    vprint("LoadingFromShelfToExtractor activated", LogColor::ExtractorColor);
    Seize(*shedBeekeeper, 2);
    vprint("LoadingFromShelfToExtractor started", LogColor::ExtractorColor);
    Wait(Uniform(TIME_TO_PUT_FRAME - 2, TIME_TO_PUT_FRAME + 2));

    shelf--;
    extractor->loadIntoExtractor(this);

    vprint("LoadingFromShelfToExtractor completed", LogColor::ExtractorColor);
    Release(*shedBeekeeper);
    if (shelf && extractor->isExtractorFree()) {
        new LoadingFromShelfToExtractor();
    }
}

// p 0
void GetAndLoadUncappedFrames::Behavior() {
    Seize(*shedBeekeeper);
    vprint("GetAndLoadUncappedFrames activated", LogColor::ExtractorColor);
    g_transport->unloadFromTransport();
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
    vprint("ExtractorRunning activated", LogColor::ExtractorColor);
    extractor->startRunning();
    again:
    Wait(TIME_OF_EXTRACTOR_RUNNING);
    vprint("Extractor finished running", LogColor::ExtractorColor);

    if (Random() <= PERC_EXTRACTOR_AGAIN) {
        vprint("Extractor started again", LogColor::ExtractorColor);
        goto again;
    }
    extractor->stopRunning();
    if (g_transport->transportAvailableForLoad(Location::Shed) && !extractor->isExtractorFree()) {
        new UnloadExtractor();
    }

    if (shelf && extractor->isExtractorFree()) {
        new LoadingFromShelfToExtractor();
    }
}