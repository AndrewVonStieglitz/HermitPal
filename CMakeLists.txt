cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add glfw
add_subdirectory(external/glfw)
include_directories(external/glfw/include)

# Include glad header files
include_directories(external/glad/include) # Adjust path if needed

# Add your executable with glad.c
add_executable(MyExecutable src/main.cpp external/glad/src/glad.c) # Adjust glad.c path if needed

# Linking
target_link_libraries(MyExecutable glfw)
