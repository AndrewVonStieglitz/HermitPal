cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# SDL
add_subdirectory(external/SDL)
include_directories(${SDL2_INCLUDE_DIRS} external/SDL/include)

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# GLAD
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(MyExe src/main.cpp)

# Linking SDL, GLFW, and GLAD to the executable
target_link_libraries(MyExe SDL2main SDL2 glfw glad)
