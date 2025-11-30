#include "../../../inc/simlib_components/BaseComponents.hpp"
#include "../../../inc/utils.hpp"

using namespace BaseConstants;

bool Extractor::isExtractorFree() {
    return this->isFree;
}

void Extractor::loadIntoExtractor(Entity* caller) {

    vprint("Enter Extractor", LogColor::Default);

    ExtractorS.Enter(caller, 1);
    if (this->ExtractorS.Full()) {
        isFree = false;
    }
}

void Extractor::unloadFromExtractor() {
    vprint("leave in extractor", LogColor::Default);
    ExtractorS.Leave(1);
    vprint("Frame unloaded from extractor", LogColor::ExtractorColor);
    if (this->ExtractorS.Empty()) {
        isFree = true;
        if (shelf) {
            for (int i = 0; i < std::min(shelf, extractor->capacity()); i++) {
                new LoadingFromShelfToExtractor();
            }
        }
    }
}