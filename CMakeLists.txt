cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# SDL
add_subdirectory(external/SDL)
include_directories(${SDL2_INCLUDE_DIRS} external/SDL/include)


add_executable(MyExe src/main.cpp)
target_link_libraries(MyExe SDL2main SDL2)
