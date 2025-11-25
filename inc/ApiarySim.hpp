#ifndef __APIARY_SIM
#define __APIARY_SIM

#include <memory>
#include <unordered_map>
#include <string>
#include "strategies/SimulationStrategy.hpp"


class ApiarySim {

public:
    void setStrategy(std::unique_ptr<SimulationStrategy> s);

    void run();

private:
    std::unique_ptr<SimulationStrategy> strategy;
};

#endif // __APIARY_SIM