#include <iostream>
#include <memory>
#include <string>

#include "../inc/ApiarySim.hpp"
#include "../inc/OnSiteExtractionStrategy.hpp"
#include "../inc/OffSiteExtractionStrategy.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <on|off>\n";
        return 1;
    }

    std::string strategyName = argv[1];

    ApiarySim sim;

    if (strategyName == "on") {
        sim.setStrategy(std::make_unique<OnSiteExtractionStrategy>());
    } else if (strategyName == "off") {
        sim.setStrategy(std::make_unique<OffSiteExtractionStrategy>());
    } else {
        std::cerr << "Unknown strategy: " << strategyName << "\n";
        return 1;
    }

    sim.run();

    return 0;
}
