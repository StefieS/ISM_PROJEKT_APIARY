#ifndef __EXTRACTOR
#define __EXTRACTOR

class Extractor {
public:
    Extractor(int capacity)
        : ExtractorS("Extractor", capacity),
          isFree(true) {}
    void loadIntoExtractor(Entity* caller);
    void unloadFromExtractor();

    bool isExtractorFree();
private:
    Store ExtractorS;
    bool isFree;
};

#endif // __EXTRACTOR