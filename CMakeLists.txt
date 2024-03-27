cmake_minimum_required(VERSION 3.10)

project(MySDLProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(external/SDL)

include_directories(${SDL2_INCLUDE_DIRS} external/SDL/include)

add_executable(MySDLApp src/main.cpp)

target_link_libraries(MySDLApp SDL2main SDL2)
