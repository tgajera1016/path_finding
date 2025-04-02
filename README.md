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
   
    - Run unit tests (can also be run through Visual Studio Test → Test Explorer)
      - cd build/tests/Debug
      - unit_tests.exe

#  Class Details (Highlevel)
  - point_2D - to manage 2D points (integer)
    
      ![image](https://github.com/user-attachments/assets/932d1341-76dd-4769-b63b-dfc589012d42)
    
  - unit - to represents the unit's position on the battlefield grid
    
      ![image](https://github.com/user-attachments/assets/220b614c-78ca-4f2a-acdf-00f3ce2e6b3b)
    
  - battle_field - to represent a grid of tiles
    
      ![image](https://github.com/user-attachments/assets/0dd19db9-2f63-42d4-a61b-dcf71b1c7d6b)
    
  - battle_field_creator - to create battlefield based on the user input
    
      ![image](https://github.com/user-attachments/assets/087a72b4-0af6-4238-aa96-15de92f05dc8)
    
  - battle_field_renderer - to renderer units position on console using double buffering
    
      ![image](https://github.com/user-attachments/assets/d75c78f7-ed0e-4abe-b930-5735231bacfe)
          
  - node - to represent the node in the A Start pathfinding graph
    
      ![image](https://github.com/user-attachments/assets/f8084e92-b2f2-49db-946e-2aef2726eae1)
    
  - pathfinder - to find the shortest path between two positions using A Start algorithm
    
      ![image](https://github.com/user-attachments/assets/38334788-6703-4aeb-9143-f55061a610b9)

  - tile_type - to identify each tile in the grid (battlefield)
  - move_status - to identify the units movement status

# Resources
  - There are total of 5 different types of JSON available as listed below, including one from the assessment in the /resources directory. If you would like to load a different JSON from the default, you would need to change the hard-coded path in battleFieldCreator.cpp
    
      	// Load battlefield configuration from a JSON file
      	**std::string config_file = "../resources/tile_set_woodland_1.json";**
      	if (!std::filesystem::exists(config_file))
      		throw std::runtime_error("Resource file not found: " + config_file);
      	battle_field.load_from_json(config_file);
      	break;
    
      - tile_set_woodland_1.json (default)
      - tile_set_woodland_2.json
      - tile_set_woodland_3.json
      - tile_set_woodland_4.json
      - tile_set_woodland_5.json






