#ifndef __BASE_COMPONENTS
#define __BASE_COMPONENTS

#include <simlib.h>
#include <memory>

inline int hives_to_open = 40;
class ITransportGetter;
inline std::unique_ptr<ITransportGetter> Transport;
inline std::unique_ptr<Facility> hiveBeekeeper;

enum class Location {
    Hives,
    Shed
};

enum class TransportStatus {
    ReadyToLoad,
    WaitingForTransport,
    ReadyToUnload
};

class ITransportGetter {
public:
    virtual bool TransportAvailable() = 0;
    virtual void insertIntoTransport() = 0;
    virtual void removeFromTransport() = 0;

};

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
