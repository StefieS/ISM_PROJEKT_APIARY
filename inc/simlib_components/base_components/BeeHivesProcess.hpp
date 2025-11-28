#ifndef __BEE_HIVES_PROCESS
#define __BEE_HIVES_PROCESS

class ReturningEmptyFramesToHive : public Process {
public:
    void Behavior() override;
    ReturningEmptyFramesToHive() {
        Activate();
    }
};

class LoadingFromStandToTransport : public Process {
public:
    void Behavior() override;
    LoadingFromStandToTransport() {
        Activate();
    }
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