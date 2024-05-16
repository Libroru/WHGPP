cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(WHGPP)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Recursively find all source files in the lib directory
file(GLOB_RECURSE LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.hpp)

# List all the source files
set(SOURCE_FILES
    src/main.cpp
    ${LIB_SOURCES}
)

# Check the source files
message(STATUS "Source files: ${SOURCE_FILES}")

add_executable(WHGPP ${SOURCE_FILES})

target_link_libraries(WHGPP ${SDL2_LIBRARIES})
