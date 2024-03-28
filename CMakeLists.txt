cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the GLFW directory
add_subdirectory(external/glfw)

# Include directories for GLFW and the header-only GLAD
include_directories(
    external/glfw/include
    external/glfw/deps
)

# Define the executable with just main.cpp
add_executable(MyExecutable src/main.cpp)

# Link GLFW with your application
target_link_libraries(MyExecutable glfw)
