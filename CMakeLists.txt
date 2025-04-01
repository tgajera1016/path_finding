cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0091 NEW)

project(path_finding)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Add the static library target
add_library(path_finding_lib STATIC
	source/unit.cpp
	source/pathFinder.cpp
	source/battleField.cpp
	source/battleFieldCreator.cpp
	source/battleFieldRenderer.cpp
	
	headers/unit.hpp
	headers/node.hpp
	headers/point2d.hpp
	headers/pathFinder.hpp
	headers/battleField.hpp
	headers/moveStatus.hpp
	headers/tileType.hpp
	headers/battleFieldCreator.hpp
	headers/battleFieldRenderer.hpp
)

# Include directories for path_finding_lib
target_include_directories(path_finding_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# Add the executable (main app)
add_executable(path_finding
    source/main.cpp
)

# Link the main app with the static library
target_link_libraries(path_finding PRIVATE path_finding_lib)

# FetchContent for third-party libraries
include(FetchContent)

# Fetch nlohmann_json
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3  # Specify the version/tag of nlohmann_json you want to use
)
FetchContent_MakeAvailable(json)
target_link_libraries(path_finding_lib PRIVATE nlohmann_json::nlohmann_json)

# Copy config files to the build output directory
add_custom_command(
    TARGET path_finding POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:path_finding>/resources
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/resources/tile_set_woodland_1.json
        ${CMAKE_SOURCE_DIR}/resources/tile_set_woodland_2.json
        ${CMAKE_SOURCE_DIR}/resources/tile_set_woodland_3.json
        ${CMAKE_SOURCE_DIR}/resources/tile_set_woodland_4.json
        ${CMAKE_SOURCE_DIR}/resources/tile_set_woodland_5.json
        $<TARGET_FILE_DIR:path_finding>/resources/
)

# Set path_finding as the startup project in Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT path_finding)

# Add the test directory
add_subdirectory(tests)