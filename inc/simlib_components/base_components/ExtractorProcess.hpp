#ifndef __EXTRACTOR_PROCESS
#define __EXTRACTOR_PROCESS
#include "../../utils.hpp"
class ExtractorRunning : public Process {
public:
    void Behavior() override;
    ExtractorRunning() {
        Activate();
    }
}; 

class LoadingFromShelfToExtractor : public Process {
public:
    void Behavior() override;
    LoadingFromShelfToExtractor() {
        Activate();
    }
}; 

class UnloadExtractor : public Process {
public:
    void Behavior() override;
    UnloadExtractor() {
        Activate();
    }
};

class GetAndLoadUncappedFrames : public Process {
public:
    void Behavior() override;
    GetAndLoadUncappedFrames() {
        Activate();
    }
};

class TakeBucketHoneyAway : public Process {
public:
    void Behavior() override;
    TakeBucketHoneyAway() {
        Activate();
    }
};

#endif // __EXTRACTOR_PROCESS