cmake_minimum_required(VERSION 3.26)
project(AdvancedC)

set(CMAKE_CXX_STANDARD 20)

add_executable(AdvancedC src/main.cpp
        src/Krankenhaus.cpp
        src/Krankenhaus.h
        src/Patient.cpp
        src/Patient.h
        src/Angestellter.cpp
        src/Angestellter.h
        src/Terminkalender.cpp
        src/Terminkalender.h)
