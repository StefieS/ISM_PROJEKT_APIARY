#ifndef __TRANSPORT_PROCESS
#define __TRANSPORT_PROCESS
#include <simlib.h>
#include "./InterfaceTransport.hpp"

class TransportingFrames : public Process {
public:
    void Behavior() override;
    TransportingFrames(Location location, int transportTime)
        : location(location), transportTime(transportTime) {}
private:
    Location location;
    int transportTime;
};

class Timer : public Process {
public:
    void Behavior() override;
    Timer(int time, int id) 
        : time(time), restart(false), stop(false), id(id) {
            Activate();
        }
    void setRestart(bool to);
    void setStop(bool to);
    
private:
    int time;
    bool restart;
    bool stop;
    int id;
};

#endif // __TRANSPORT_PROCESS