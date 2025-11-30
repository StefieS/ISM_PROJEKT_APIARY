#ifndef __BEE_HIVES_PROCESS
#define __BEE_HIVES_PROCESS

class ReturningEmptyFramesToHive : public Process {
public:
    void Behavior() override;
    ReturningEmptyFramesToHive() {
        this->Priority = 3;
        Activate();
    }
};

class LoadingFromStandToTransport : public Process {
public:
    void Behavior() override;
    LoadingFromStandToTransport() {
        this->Priority = 2;
        Activate();
    }
};

class TakingOutFrames : public Process {
public:
    void Behavior() override;
    TakingOutFrames() {
        this->Priority = 1;
        Activate();
    }
};

class OpeningHive : public Process {
public:
    void Behavior() override;
    OpeningHive() {
        this->Priority = 0;
        Activate();
    }
};

#endif // __BEE_HIVES_PROCESS