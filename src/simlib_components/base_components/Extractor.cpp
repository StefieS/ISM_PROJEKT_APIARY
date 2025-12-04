#include "../../../inc/simlib_components/BaseComponents.hpp"
#include "../../../inc/utils.hpp"

using namespace BaseConstants;

bool Extractor::isExtractorFree() {
    return this->isFree;
}

void Extractor::loadIntoExtractor(Entity* caller) {
    double t0 = Time; // waiting to enter extractor

    vprint("Enter Extractor", LogColor::Default);

    ExtractorS.Enter(caller, 1);
    if (this->ExtractorS.Full()) {
        isFree = false;
    }

    stat_waitToEnterExtractor(Time - t0); // record wait before entering extractor

}

void Extractor::unloadFromExtractor() {
    double t0 = Time; // waiting to unload

    vprint("leave in extractor", LogColor::Default);
    ExtractorS.Leave(1);
    vprint("Frame unloaded from extractor", LogColor::ExtractorColor);

    stat_waitToUnloadExtractor(Time - t0); // record extractor unload wait
    
    if (this->ExtractorS.Empty()) {
        isFree = true;
        if (shelf) {
            for (int i = 0; i < std::min(shelf, extractor->capacity()); i++) {
                new LoadingFromShelfToExtractor();
            }
        }
    }
}