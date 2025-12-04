#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <cstdlib>

#include "../inc/ApiarySim.hpp"
#include "../inc/strategies/OnSiteExtractionStrategy.hpp"
#include "../inc/strategies/OffSiteExtractionStrategy.hpp"
#include "../inc/constants/BaseConstants.hpp"

// Convert string to lowercase
std::string lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// Parse true/false as bool
bool parseBool(const std::string& s, bool& out) {
    std::string v = lower(s);
    if (v == "true" || v == "1") { out = true; return true; }
    if (v == "false" || v == "0") { out = false; return true; }
    return false;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] 
                  << " <on|off> [true|false] [-v] [hives]\n";
        return 1;
    }

    // Parse -v anywhere
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-v") {
            globalVerbose = true;
        }
    }

    std::string strategyName = lower(argv[1]);
    ApiarySim sim;

    int lastArgIndex = argc - 1;

    // Try to parse last argument as integer (hive count)
    int configuredHives = BaseConstants::HIVES_TO_OPEN; // default
    if (std::isdigit(argv[lastArgIndex][0])) {
        configuredHives = std::atoi(argv[lastArgIndex]);
        if (configuredHives > 0) {
            BaseConstants::HIVES_TO_OPEN = configuredHives;
        }
    }

    if (strategyName == "on") {
        if (argc < 3) {
            std::cerr << "Error: 'on' strategy requires boolean argument (true/false)\n";
            return 1;
        }

        bool flag;
        if (!parseBool(argv[2], flag)) {
            std::cerr << "Error: invalid boolean value '" << argv[2]
                      << "'. Use true/false.\n";
            return 1;
        }

        sim.setStrategy(std::make_unique<OnSiteExtractionStrategy>(flag));
    }
    else if (strategyName == "off") {
        sim.setStrategy(std::make_unique<OffSiteExtractionStrategy>());
    }
    else {
        std::cerr << "Unknown strategy: '" << strategyName << "'\n";
        return 1;
    }

    if (globalVerbose) {
        std::cout << "Verbose mode enabled\n";
        std::cout << "Hives to open: " << BaseConstants::HIVES_TO_OPEN << "\n";
    }

    sim.run();
    return 0;
}
