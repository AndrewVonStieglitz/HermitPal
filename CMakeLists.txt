cmake_minimum_required(VERSION 3.10)

project(MySDLProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the SDL subdirectory
add_subdirectory(external/SDL)

# Include directories for SDL
include_directories(${SDL2_INCLUDE_DIRS} external/SDL/include)

# Add the GLFW subdirectory
add_subdirectory(external/glfw)

# Create your executable
add_executable(MySDLApp src/main.cpp)

# Link libraries to your executable
# Link both SDL and GLFW libraries
target_link_libraries(MySDLApp SDL2main SDL2 glfw)

# Note: No need to manually include directories for GLFW when using add_subdirectory,
# as it will handle include paths for targets automatically.
