cmake_minimum_required(VERSION 3.22)
project(AdvancedC)

# Set C++ Standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find GTKmm
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

# Include directories for GTKmm
include_directories(${GTKMM_INCLUDE_DIRS})

# Set source files
set(SOURCES
        main.cpp
        src/Game.cpp
        src/GameRenderer.cpp
        src/style.h
)

# Add executable
add_executable(AdvancedC ${SOURCES})

# Link GTKmm libraries
target_link_libraries(AdvancedC ${GTKMM_LIBRARIES})
