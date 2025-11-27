#include "../../../inc/simlib_components/BaseComponents.hpp"
#include "../../../inc/constants/BaseConstants.hpp"
#include "../../../inc/utils.hpp"

using namespace BaseConstants;

bool Extractor::isExtractorFree() {
    return this->isFree;
}

void Extractor::loadIntoExtractor(Entity* caller) {
    ExtractorS.Enter(caller, 1);
    vprint("Frame loaded into extractor");
    if (this->ExtractorS.Full()) {
        isFree = false;
        new ExtractorRunning();
    }
}

void Extractor::unloadFromExtractor() {
    ExtractorS.Leave(1);
    vprint("Frame unloaded from extractor");
    if (this->ExtractorS.Empty()) {
        isFree = true;
    }
}