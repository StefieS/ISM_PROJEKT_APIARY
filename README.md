# ISM_PROJEKT_APIARY

> Discrete event simulation of an apiary to compare the effectiveness of onsite versus offsite honey extraction methods.

## 📋 Overview

This project implements a simulation model of a beekeeping operation (apiary) to analyze and compare two different honey extraction strategies:

- **Onsite extraction**: Honey is extracted directly at the apiary location
- **Offsite extraction**: Honey frames are transported to a separate extraction facility

The simulation helps determine which method is more efficient in terms of time, resources, and overall productivity.

## 🎯 Project Goals

- Model realistic apiary operations throughout the beekeeping season
- Simulate bee colony behavior and honey production cycles
- Compare operational efficiency between extraction methods
- Analyze throughput, resource utilization, and time management
- Provide data-driven insights for beekeeping management decisions

## 🛠️ Technology Stack

- **Language**: C++ (83.2%)
- **Simulation Library**: SIMLIB - discrete event simulation framework
- **Documentation**: LaTeX (10.4%)
- **Data Visualization**: Gnuplot (2.9%) - for generating graphs and plots
- **Build System**: Make

### About SIMLIB

SIMLIB is a C++ library for discrete event simulation and continuous system modeling. It provides:
- Event scheduling and management
- Statistical data collection and analysis
- Random number generation with various distributions
- Facilities and queuing systems modeling
- Histogram and time-series output

## 📁 Project Structure

```
ISM_PROJEKT_APIARY/
├── src/              # Source code files
├── inc/              # Header files
├── simlib/           # SIMLIB simulation library
├── figs/             # Generated figures and graphs
├── Makefile          # Build configuration
├── ims_doku.pdf      # Project documentation
└── README.md         # This file
```

## 🚀 Getting Started

### Prerequisites

- C++ compiler (g++ recommended)
- Make
- SIMLIB library

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/StefieS/ISM_PROJEKT_APIARY.git
   cd ISM_PROJEKT_APIARY
   ```

2. **Install SIMLIB library**
   ```bash
   cd simlib
   sudo make install
   cd ..
   ```

3. **Build the project**
   ```bash
   make
   ```
   
   This will create the `simulation` executable in your project directory.

## 📊 Running the Simulation

After building the project, run the simulation executable:

```bash
./simulation <strategy> [options]
```

### Command Line Syntax

```
./simulation <on|off> [true|false] [-v] [hives]
```

### Parameters

- **`<on|off>`** (required): Extraction strategy
  - `on` - Onsite extraction method
  - `off` - Offsite extraction method

- **`[true|false]`** (required for `on` strategy): Additional configuration flag for onsite extraction

- **`[-v]`** (optional): Enable verbose mode for detailed output

- **`[hives]`** (optional): Number of hives to simulate (positive integer)

### Usage Examples

**Onsite extraction with flag enabled, 50 hives:**
```bash
./simulation on true 50
```

**Onsite extraction with flag disabled, verbose mode:**
```bash
./simulation on false -v
```

**Offsite extraction with 75 hives:**
```bash
./simulation off 75
```

**Offsite extraction with verbose output:**
```bash
./simulation off -v
```

**Offsite extraction with default settings and verbose mode:**
```bash
./simulation off -v 30
```

### Output

The simulation produces:
- Statistical analysis of both extraction methods
- Performance metrics (throughput, waiting times, resource utilization)
- Visualization graphs (in the `figs/` directory)
- Comparison data for decision-making
- SIMLIB statistical reports and histograms
- Verbose runtime information (when `-v` flag is used)

## 📈 Simulation Model

The model incorporates:

- **Bee colonies**: Individual hive behavior and honey production patterns
- **Seasonal cycles**: Nectar flow periods and colony dynamics throughout the year
- **Extraction processes**: Time requirements and resource constraints for both methods
- **Transportation**: Logistics and time overhead for offsite extraction method
- **Resource management**: Equipment availability, worker allocation, and facility utilization
- **Queuing systems**: Waiting times when extraction facilities are busy
- **Stochastic elements**: Random variations in honey production and processing times

### Modeled Scenarios

The simulation compares:

**Onsite Extraction:**
- Extraction performed directly at apiary location
- Minimal transportation time
- Limited by onsite equipment capacity
- Potential for slower extraction due to simpler equipment

**Offsite Extraction:**
- Frames transported to dedicated extraction facility
- Transportation time and logistics overhead
- Access to professional extraction equipment
- Potentially faster extraction with better equipment
- Shared facility may have queuing delays

## 🔬 Experiments

The simulation allows for various experimental setups:
- Different colony counts (specify via command line)
- Comparing onsite vs offsite extraction strategies
- Testing different configurations for onsite extraction (true/false flag)
- Observing system behavior with varying hive counts
- Analyzing resource utilization patterns

### Running Experiments

**Compare both strategies with same hive count:**
```bash
./simulation on true 50 -v > onsite_true_50.txt
./simulation on false 50 -v > onsite_false_50.txt
./simulation off 50 -v > offsite_50.txt
```

**Test scalability with different hive counts:**
```bash
for hives in 10 25 50 75 100; do
    ./simulation off $hives > results_off_${hives}.txt
done
```

**Verbose comparison for detailed analysis:**
```bash
./simulation on true -v 30
./simulation off -v 30
```

### Analyzing Results

The simulation generates:
- Statistical summaries (mean, variance, confidence intervals)
- Time-series data of production metrics
- Utilization statistics for resources
- Comparison charts between methods
- Gnuplot scripts for visualization (in `figs/` directory)

## 📄 Documentation

Detailed project documentation is available in `ims_doku.pdf` (in Czech language), which includes:
- Theoretical background
- Model design and assumptions
- Implementation details
- Experimental results and analysis
- Conclusions and recommendations

## 👥 Authors

- Mikuláš Lešiga (xlesigm00)
- Filip Novák (xnovakf00)

## 📜 License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## 🐝 About Beekeeping Simulation

This simulation is designed for educational and research purposes to understand:
- Operational efficiency in apiary management
- Resource optimization in honey production
- Decision-making factors for extraction method selection
- Time and cost trade-offs in beekeeping operations

## 🤝 Contributing

This is an academic project. For questions or suggestions, please open an issue in the GitHub repository.

## 📞 Contact

For inquiries about this project, please contact the authors through their university emails or create an issue on GitHub.

---

**Note**: This project was created as part of the IMS (Modeling and Simulation) course curriculum.
