# Micromouse 2.0

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language: C++](https://img.shields.io/badge/Language-C++-blue.svg)]()
[![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino-success.svg)]()

An embedded systems robotics project implementing an autonomous maze-solving robot with advanced pathfinding algorithms. Designed to efficiently navigate and solve mazes using real-time sensor feedback and intelligent navigation strategies.

## Table of Contents

- [About](#about-this-project)
- [Features](#features)
- [Architecture](#architecture)
- [Algorithms](#algorithms)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Getting Started](#getting-started)
- [How It Works](#how-it-works)
- [Contributing](#contributing)
- [License](#license)

## About This Project

Micromouse 2.0 is a sophisticated autonomous robotic system designed to navigate and solve mazes using embedded C++ and Arduino hardware. The robot dynamically maps a 16x16 cell maze grid as it explores, identifies wall configurations, and computes optimal paths to reach the target destination. This project demonstrates core concepts in embedded systems, real-time sensor processing, pathfinding algorithms, and robotics control systems.

**Key Objective**: Navigate a maze autonomously and reach the goal cell with minimal exploration.

## Features

- **Autonomous Maze Navigation**: Self-governing operation without external control or human intervention
- **Real-time Sensor Integration**: Multi-sensor input processing for wall and obstacle detection
- **Advanced Pathfinding**: Implements optimized maze-solving algorithms for efficient route calculation
- **Dynamic Wall Mapping**: Continuous detection and mapping of maze walls during exploration
- **Arduino-based Embedded System**: Leverages Arduino platform for reliable and accessible embedded development
- **Serial Communication Protocol**: Logging and diagnostic capabilities via serial interface (19200 baud)
- **Motion Control**: Configurable forward movement and rotational dynamics with speed parameters
- **Cell-based Grid Representation**: Structured maze representation using linearized cell coordinates

## Architecture

The system follows a modular embedded systems architecture:

```
┌─────────────────────────────────┐
│   Main Control Loop (Arduino)   │
│   (Micromouse_Arduino.ino)      │
└────────────┬────────────────────┘
             │
    ┌────────┴────────┐
    │                 │
┌───▼────────┐   ┌───▼──────────┐
│   Sensor   │   │ Navigation   │
│  Interface │   │   Engine     │
│  (Api.h)   │   │ (treamux.h)  │
└────────────┘   └──────────────┘
```

## Algorithms

### Treamux Algorithm

The **Treamux** algorithm is the core navigation engine responsible for maze traversal and pathfinding:

- **Flood-Fill Integration**: Combines flood-fill algorithm for distance calculation from any cell to the target
- **Wall Tracking**: Maintains a binary representation of wall adjacencies for each cell
- **Neighbor Evaluation**: Uses macro-optimized neighbor distance queries for efficient pathfinding
- **Dynamic Path Recalculation**: Updates path based on newly discovered walls
- **Movement Optimization**: Determines next optimal cell based on proximity to target and wall constraints

Key components:

- `wallExists()`: Checks wall presence between cells using bitwise operations
- `getNeighbourDistance()`: Calculates accessible neighbor distances
- `updateTargetCell()`: Updates the next target cell in the path
- `goToTargetCell()`: Executes movement toward the calculated target

## Project Structure

```
micromouse_2.0/
├── Micromouse_Arduino.ino     # Main sketch - control loop and initialization
├── Api.h / Api.cpp             # Core API - robot control & sensor interface
├── treamux.h / treamux.cpp     # Pathfinding engine & maze traversal logic
├── globals.h                   # Global variables & constants
├── test.cpp                    # Unit testing utilities
└── README.md                   # Project documentation
```

### File Descriptions

| File                        | Purpose                                                      |
| --------------------------- | ------------------------------------------------------------ |
| `Micromouse_Arduino.ino`    | Main Arduino sketch containing setup and event loop          |
| `Api.h` / `Api.cpp`         | Public API for robot movement, sensor queries, and logging   |
| `treamux.h` / `treamux.cpp` | Pathfinding algorithms, maze traversal, and navigation logic |
| `globals.h`                 | Shared definitions, constants, and global state              |
| `test.cpp`                  | Testing framework and validation utilities                   |

## Requirements

### Hardware

- Arduino compatible microcontroller (ATmega328P or equivalent)
- 4x Proximity/Ultrasonic sensors (front, rear, left, right)
- Motor drivers and actuators
- Serial communication module

### Software

- Arduino IDE or compatible compiler
- C++ compiler with Arduino support
- Serial monitor for debugging (19200 baud)

## Getting Started

### Setup

1. Install Arduino IDE from [arduino.cc](https://www.arduino.cc/)
2. Configure board settings for your Arduino microcontroller
3. Connect sensors and actuators according to the hardware specifications
4. Upload `Micromouse_Arduino.ino` to the Arduino board

### Building

```bash
# Compile using Arduino IDE or
arduino-cli compile --fqbn arduino:avr:uno
```

### Running

1. Open Serial Monitor at 19200 baud
2. Power the robot
3. The robot will initialize and begin maze exploration automatically

## How It Works

The autonomous navigation system operates in the following sequence:

1. **Initialization**: Setup sensor interfaces, serial communication, and maze grid structures
2. **Sensor Scanning**: Continuously poll proximity sensors to detect adjacent walls
3. **Wall Mapping**: Update the maze representation with detected wall positions
4. **Pathfinding**: Execute Treamux algorithm to calculate optimal path to target cell
5. **Movement Execution**: Drive motors to move forward or rotate as needed
6. **Goal Validation**: Check if target cell has been reached
7. **Loop**: Repeat steps 2-6 until maze is solved

### Main Control Flow

```cpp
while(currentCell != targetCellsGoal) {
    updateWalls();          // Detect and map walls
    treamux();              // Run pathfinding engine
    updateTargetCell();     // Calculate next target
    // Execute movement
}
```

## Contributing

Contributions are welcome! Please follow these guidelines:

- Write clear, documented code
- Follow the existing code style and conventions
- Add appropriate comments for complex logic
- Test changes thoroughly before submission
- Update documentation as needed

## License

This project is licensed under the MIT License - see LICENSE file for details.
