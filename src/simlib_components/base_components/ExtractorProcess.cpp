#include "../../../inc/simlib_components/BaseComponents.hpp"
#include "../../../inc/utils.hpp"

using namespace BaseConstants;

void TakeBucketHoneyAway::Behavior() {
        Wait(0.01);

    vprint("TakeBucketHoneyAway activated", LogColor::ExtractorColor);
    Seize(*shedBeekeeper);
    vprint("Taking bucket of honey away", LogColor::ExtractorColor);
    Wait(Uniform(BUCKET_TAKING_TIME - 5, BUCKET_TAKING_TIME + 5));
    extractedHoney -= BUCKET_CAPACITY;
    vprint("Bucket of honey taken away", LogColor::ExtractorColor);
    Wait(0.01);
    currentStrategy->onBucketReady();
    Release(*shedBeekeeper);
}



// p 3
void UnloadExtractor::Behavior() {
    Wait(0.01);

    vprint("UnloadExtractor spawned", LogColor::ExtractorColor);
    Seize(*shedBeekeeper);
    double t0 = Time; // waiting to unload extractor

    vprint("UnloadExtractor seized", LogColor::ExtractorColor);
    Wait(Uniform(TIME_TO_UNLOAD_FRAME_FROM_EXTRACTOR - 2, TIME_TO_UNLOAD_FRAME_FROM_EXTRACTOR + 2));
    extractor->unloadFromExtractor();
    if (!g_transport->transportAvailableForLoad(Location::Shed)) {
        vprint("No transport available for unload, putting on shelf", LogColor::ExtractorColor);
        emptyShelf++;
    } else {
        g_transport->loadIntoTransport(this);
    }
    
    stat_waitToUnloadExtractor(Time - t0); // record time waited to unload

    vprint("Unloaded one frame from extractor", LogColor::ExtractorColor);
    Wait(0.01);
    Release(*shedBeekeeper);
}

// p 2
void LoadingFromShelfToExtractor::Behavior() {
        Wait(0.01);

    // TODO: spawn when extractor available to load and shelf != 0
    vprint("LoadingFromShelfToExtractor activated", LogColor::ExtractorColor);
    Seize(*shedBeekeeper);
    vprint("LoadingFromShelfToExtractor started", LogColor::ExtractorColor);
    Wait(Uniform(TIME_TO_PUT_FRAME - 2, TIME_TO_PUT_FRAME + 2));

    shelf--;
    extractor->loadIntoExtractor(this);

    vprint("LoadingFromShelfToExtractor completed", LogColor::ExtractorColor);
                Wait(0.01);

    Release(*shedBeekeeper);
    if (!extractor->isExtractorFree()) {
        new ExtractorRunning();
    }
}

void FromShelfToTransport::Behavior() {

    vprint("FromShelfToTransport spawned", LogColor::ExtractorColor);
    Seize(*shedBeekeeper);
    vprint("FromShelfToTransport started", LogColor::ExtractorColor);
    Wait(Uniform(TIME_TO_PUT_FRAME - 2, TIME_TO_PUT_FRAME + 2));

    emptyShelf--;
    g_transport->loadIntoTransport(this);

    vprint("FromShelfToTransport completed", LogColor::ExtractorColor);
    Release(*shedBeekeeper);
}

void GetAndLoadUncappedFrames::Behavior() {
        Wait(0.01);

    vprint("GetAndLoadUncappedFrames spawned", LogColor::ExtractorColor);
    Seize(*shedBeekeeper);
    vprint("GetAndLoadUncappedFrames seized", LogColor::ExtractorColor);
    Wait(0.01);
    g_transport->unloadFromTransport();
    if (Random() <= PERC_LONG_UNCAPPING) {
        Wait(Normal(TIME_OF_LONG_UNCAPPING, 10));
    } else {
        Wait(Normal(TIME_OF_SHORT_UNCAPPING, 5));
    }

    Wait(TIME_TO_PUT_FRAME);

    if (extractor->isExtractorFree()) {
        extractor->loadIntoExtractor(this);
                    Wait(0.01);

        Release(*shedBeekeeper);
        if (!extractor->isExtractorFree()) {
            new ExtractorRunning();
        }
    } else {
        shelf++;
        vprint("shelf++");
                    Wait(0.01);

        Release(*shedBeekeeper);
    }

}

void ExtractorRunning::Behavior() {
    Wait(0.01);
    double t0 = Time; // start of extractor run

    vprint("ExtractorRunning activated", LogColor::ExtractorColor);
    extractor->startRunning();
    again:
    Wait(TIME_OF_EXTRACTOR_RUNNING);

    stat_extractorRunningTime(Time - t0); // record running time

    vprint("Extractor finished running", LogColor::ExtractorColor);
    extractedHoney += HONEY_PER_EXTRACTOR_RUN;
    Wait(0.01);

    if (extractedHoney >= BUCKET_CAPACITY) {
        new TakeBucketHoneyAway();
    }

    if (Random() <= PERC_EXTRACTOR_AGAIN) {
        vprint("Extractor started again", LogColor::ExtractorColor);
        goto again;
    }
    extractor->stopRunning();
        Wait(0.01);

    if (g_transport->transportAvailableForLoad(Location::Shed) && !extractor->isExtractorFree()) {
        for (int i = 0; i < extractor->capacity(); i++) {
            new UnloadExtractor();
        }
    } else if (!extractor->isExtractorFree()) {
        for (int i = 0; i < extractor->capacity(); i++) {
            new UnloadExtractor();
        }
    }
}

void StrainingBucketOnSite::Behavior() {
    vprint("Bucket ready - waiting for all hives to finish", LogColor::ExtractorColor);
    
    bucketsWaitingToStrain.Insert(this);
    Passivate();
    
    vprint("All hives done - starting straining", LogColor::ExtractorColor);
    Wait(STRAINING_TIME);
    vprint("Bucket strained", LogColor::ExtractorColor);
}

void StrainingBucketOffSite::Behavior() {
    vprint("Starting straining immediately", LogColor::ExtractorColor);
    Wait(STRAINING_TIME);
    vprint("Bucket strained", LogColor::ExtractorColor);
}

void CleanExtractor::Behavior() {
    vprint("Cleaning extractor started", LogColor::ExtractorColor);
    Seize(*shedBeekeeper);
    Wait(Uniform(currentStrategy->CleaningTime - 5*60, currentStrategy->CleaningTime + 5*60));
    vprint("Cleaning extractor completed", LogColor::ExtractorColor);
    Release(*shedBeekeeper);
}