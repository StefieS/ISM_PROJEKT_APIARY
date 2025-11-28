#ifndef __TRANSPORT_PROCESS
#define __TRANSPORT_PROCESS
#include <simlib.h>
#include "./InterfaceTransport.hpp"

class TransportingFrames: public Process {
public:
    void Behavior() override;
    TransportingFrames(Location location, int transportTime) : 
        location(location), transportTime(transportTime) {}
private:
    Location location;
    int transportTime;
};


#endif // __TRANSPORT_PROCESS