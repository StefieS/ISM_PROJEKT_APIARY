#ifndef __EXTRACTOR
#define __EXTRACTOR

class Extractor {
public:
    Extractor(int capacity)
        : ExtractorS("Extractor", capacity),
          isFree(true), running(false) {}
    void loadIntoExtractor(Entity* caller);
    void unloadFromExtractor();
    int capacity() {
        return ExtractorS.Capacity();
    }
    bool isExtractorFree();
    bool isRunning() {
        return running;
    }

    void startRunning() {
        running=true;
    }
    
    void stopRunning() {
        running=false;
    }
private:
    Store ExtractorS;
    bool isFree;
    bool running;
};

#endif // __EXTRACTOR