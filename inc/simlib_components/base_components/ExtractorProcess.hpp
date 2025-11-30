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
        this->Priority = 6;
        Activate();
    }
};

// needsto be gighet than 
class FromShelfToTransport : public Process {
public:
    void Behavior() override;
    FromShelfToTransport() {
        this->Priority = 4;
        Activate();
    }
};

class UnloadExtractor : public Process {
public:
    void Behavior() override;
    UnloadExtractor() {
        this->Priority = 3;
        Activate();
    }
};

class GetAndLoadUncappedFrames : public Process {
public:
    void Behavior() override;
    GetAndLoadUncappedFrames() {
        this->Priority = 3;
        Activate();
    }
};

class TakeBucketHoneyAway : public Process {
public:
    void Behavior() override;
    TakeBucketHoneyAway() {
        this->Priority = 5;
        Activate();
    }
};

#endif // __EXTRACTOR_PROCESS