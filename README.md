# Guide-Me: Travel Path Finder

## Overview
Guide-Me is a C++ desktop application that helps users plan travel routes across a country by reading a map from a file, calculating all possible paths between cities, and displaying available transportation options within the user's budget. Built with the Qt framework, it leverages object-oriented programming (OOP), efficient data structures, and algorithms to provide a user-friendly interface and accurate route planning.

## Features
- **Map Input**: Reads a country map from a text file specifying cities, connections, transportation modes, and costs.
- **Path Finding**: Computes all possible paths between a source and destination city using a depth-first search (DFS) algorithm.
- **Budget Filtering**: Filters transportation options based on the user's specified budget.
- **User Interface**: Interactive GUI built with Qt, allowing users to select cities, input budget, and view paths and transportation details.
- **Data Visualization**: Displays paths and transportation options in a clear, tabular format.

## Technologies Used
- **Programming Language**: C++ (C++17 standard)
- **GUI Framework**: Qt 6 for cross-platform desktop application development
- **Data Structures**:
  - Graph (adjacency list) for representing the country map
  - Vectors for storing paths and transportation options
  - Maps for efficient lookup of city and transport data
- **Algorithms**:
  - Depth-First Search (DFS) and BFS for finding all possible paths
  - Filtering algorithm for budget-based transportation selection
- **OOP Principles**:
  - Encapsulation: Classes for City, Transport, and Graph
  - Abstraction: Clean interfaces for path finding and UI
  - Modularity: Separated logic for file reading, path calculation, and GUI

## Prerequisites
- **C++ Compiler**: GCC/Clang/MSVC supporting C++17
- **Qt Framework**: Version 6.x (install via Qt Installer or package manager)
- **CMake**: Version 3.16 or higher for building the project
- **Operating System**: Windows, macOS, or Linux

## Installation
1. Clone the repository:
   ```bash
   git clone <repository-url>
   ```
2. Navigate to the project directory:
   ```bash
   cd guide-me
   ```
3. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
4. Configure the project with CMake (ensure Qt is in your PATH):
   ```bash
   cmake ..
   ```
5. Build the project:
   ```bash
   cmake --build .
   ```
6. Run the application:
   - Windows: `./guide-me.exe`
   - Linux/macOS: `./guide-me`

## Input File Format
The program reads a text file (`map.txt`) with the following format:
```
Cities: City1, City2, City3, ...
Connections:
City1 -> City2: Train(50), Bus(30)
City2 -> City3: Flight(100), Train(60)
...
```
- **Cities**: Comma-separated list of city names.
- **Connections**: Each line specifies a directed edge between two cities and available transportation modes with costs in parentheses.

Example `map.txt`:
```
Cities: NewYork, Chicago, Miami
Connections:
NewYork -> Chicago: Train(80), Bus(50)
Chicago -> Miami: Flight(150), Train(90)
NewYork -> Miami: Flight(120)
```

## Usage
1. Place a valid `map.txt` file in the application directory.
2. Launch the application.
3. In the GUI:
   - Select a **source city** and **destination city** from dropdown menus.
   - Enter your **budget** in the provided field.
   - Click **Find Paths** to compute and display all possible paths.
4. View results in a table showing:
   - Each path (sequence of cities)
   - Available transportation modes for each leg
   - Total cost (filtered to fit within budget)
5. Optionally, export results to a text file via the GUI.

## Project Structure
```
guide-me/
├── src/                   # Source code
│   ├── main.cpp           # Application entry point
│   ├── graph.h/cpp        # Graph class for map representation
│   ├── city.h/cpp         # City class for city data
│   ├── transport.h/cpp    # Transport class for transportation modes
│   ├── pathfinder.h/cpp   # Path finding logic (DFS algorithm)
│   ├── mainwindow.h/cpp   # Qt main window for GUI
│   └── fileparser.h/cpp   # File reading and parsing logic
├── resources/             # Resource files
│   └── map.txt            # Sample input file
├── CMakeLists.txt         # CMake configuration
└── README.md              # This file
```

## Building the GUI
The Qt-based GUI includes:
- **QComboBox**: For selecting source and destination cities.
- **QLineEdit**: For entering the budget.
- **QPushButton**: To trigger path finding.
- **QTableWidget**: To display paths and transportation options.
- **QFileDialog**: For loading custom map files.

## Contributing
1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add feature or fix description"
   ```
4. Push to your branch:
   ```bash
   git push origin feature-name
   ```
5. Open a pull request with a detailed description.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contact
For questions or feedback, contact [your-email@example.com](mailto:your-email@example.com).
