#ifndef __EXTRACTOR_PROCESS
#define __EXTRACTOR_PROCESS


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
};

#endif // __EXTRACTOR_PROCESS