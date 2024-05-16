cmake_minimum_required(VERSION 3.29)

project(WHGPP)


add_executable(WHGPP main.cpp)

find_package(SDL2 REQUIRED)
include_directories(WHGPP ${SDL2_INCLUDE_DIRS})

target_link_libraries(WHGPP ${SDL2_LIBRARIES})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

