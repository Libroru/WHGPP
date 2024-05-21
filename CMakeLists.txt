cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(WHGPP)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(WHGPP src/main.cpp
        src/math/vectors.cpp
        src/entity/player.cpp
        src/entity/rotating_balls.cpp
        src/core/game_manager.cpp
)

target_link_libraries(WHGPP ${SDL2_LIBRARIES})
