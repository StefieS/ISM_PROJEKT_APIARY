#ifndef __BASE_COMPONENTS
#define __BASE_COMPONENTS

#include <simlib.h>

int hives_to_open = 40;

Facility hiveBeekeeper("Hive Beekeeper");

class ReturningEmptyFramesToHive : public Process {
public:
    void Behavior() override;
private:
    // set before the activation, based on the number of empty frames the transport has
    int framesToReturn = 0; 
};

class LoadingFromStandToTransport : public Process {
public:
    void Behavior() override;
};

class TakingOutFrames : public Process {
public:
    void Behavior() override;
};

class OpeningHive : public Process {
public:
    void Behavior() override;
    OpeningHive() {
        Activate();
    }
};




#endif // __BASE_COMPONENTS
