#include "../inc/ApiarySim.hpp"
#include <iostream>


void ApiarySim::setStrategy(std::unique_ptr<SimulationStrategy> s) {
        strategy = std::move(s);
}

void ApiarySim::run() {
        if (strategy) {
                strategy->run();
        } else {
                std::cerr << "Error: No strategy set!\n";
        }
}