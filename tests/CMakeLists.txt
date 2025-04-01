cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0091 NEW)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Define test executable
add_executable(unit_tests
    unit_test_main.cpp
)

# Link static library and GoogleTest
target_link_libraries(unit_tests
    PRIVATE
    path_finding_lib
    gtest_main
)

target_compile_features(unit_tests PRIVATE cxx_std_17)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(unit_tests)
