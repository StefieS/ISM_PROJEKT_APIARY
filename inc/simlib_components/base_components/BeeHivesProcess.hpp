#ifndef __BEE_HIVES_PROCESS
#define __BEE_HIVES_PROCESS

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

#endif // __BEE_HIVES_PROCESS