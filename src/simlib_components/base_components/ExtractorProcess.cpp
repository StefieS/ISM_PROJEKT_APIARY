#include "../../../inc/simlib_components/BaseComponents.hpp"
#include "../../../inc/constants/BaseConstants.hpp"
#include "../../../inc/utils.hpp"

using namespace BaseConstants;

// p 3
void UnloadExtractor::Behavior() {
    Seize(*shedBeekeeper, 3);
    Wait(Uniform(TIME_TO_UNLOAD_FRAME_FROM_EXTRACTOR - 2, TIME_TO_UNLOAD_FRAME_FROM_EXTRACTOR + 2));
    vprint("Unloaded one frame from extractor");
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
        
        for (int i = 0; i < EXTRACTOR_CAPACITY; ++i) {
            new UnloadExtractor();
        }
    }
}