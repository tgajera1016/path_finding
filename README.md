# Overview
This project implements a pathfinding system for battle units in a real-time strategy (RTS) game. Each unit can navigate a 2D battlefield grid using the A* algorithm, avoiding elevated terrain, other units, and dynamically changing obstacles. The battlefield is defined via JSON files or generated randomly.

# Tools
Git: https://git-scm.com/downloads

CMake: https://cmake.org/download/

# Objectives
Navigate units from start to target positions on a 2D grid (battlefield) while avoiding elevated terrain (unwalkable) and occupied positions (other units). The solution must support multiple units navigating simultaneously, have a way to render unit movements for visualization, and maintain clean, modular, and testable C++ code.

# Features
Algorithm: A* to find the shortest path from start to target on grid-based maps.
Dynamic Obstacles: Re-routing if a unit blocks a path.
Custom Battlefield: Load JSON maps or generate random ones.
Console Renderer: Rendering using Windows console screen buffer API.
Unit Testing: Validated using GoogleTest framework with key edge cases.

# Project Structure
/headers         → header files

/source          → implementation files

/tests           → unit tests using GoogleTest

/resources       → JSON battlefield 

CMakeLists.txt   → CMake build script

# Third-Party Library
[nlohmann/json]
JSON parsing for battlefield map
https://github.com/nlohmann/json

[GoogleTest]
Unit testing framework
https://github.com/google/googletest

# Build Instructions (Using CMake)
[Prerequisites]

  - CMake 3.14+
  - Visual Studio 2022
  - Git (for FetchContent)

[Build Steps]
  - Clone the project and enter the directory
      - git clone https://github.com/tgajera1016/path_finding.git
      - cd path_finding

  - Create build directory
      - cmake -S . -B build

  - Compile
      - cmake --build build
        
  - Run
      - cd build/debug
      - path_finding.exe
   
    - Run unit tests
      - cd build/tests/Debug
      - unit_tests.exe

#  Class Details (Highlevel)
  - point_2D - to manage 2D points (integer)
  - tile_type - to identify each tile in the grid (battlefield)
  - unit - to represents the unit's position on the battlefield grid
  - battle_field - to represent a grid of tiles
  - battle_field_creator - to create battlefield based on the user input
  - battle_field_renderer - to renderer units position on console using double buffering
  - move_status - to identify the units movement status
  - node - to represent the node in the A Start pathfinding graph
  - pathfinder - to find the shortest path between two positions using A Start algorithm




