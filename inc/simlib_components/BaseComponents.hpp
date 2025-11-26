#ifndef __BASE_COMPONENTS
#define __BASE_COMPONENTS

#include <simlib.h>
#include <memory>

inline int hives_to_open = 40;
inline std::unique_ptr<Store> Transport;
inline std::unique_ptr<Facility> hiveBeekeeper;


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
    TakingOutFrames() {
        Activate();
    }
};

class OpeningHive : public Process {
public:
    void Behavior() override;
    OpeningHive() {
        Activate();
    }
};




#endif // __BASE_COMPONENTS
