cmake_minimum_required(VERSION 3.21.0)

project(OrganExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(PLATFORM_CPU_SISD)
set(CMAKE_CXX_FLAGS "-O3 -Wall -march=native -mtune=native")

add_subdirectory(../../.. mmft-simulator)

# main executable
add_executable(OrganExample)
target_sources(OrganExample PUBLIC Organ.cpp)
target_link_libraries(OrganExample PUBLIC simLib)
