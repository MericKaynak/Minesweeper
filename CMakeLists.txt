cmake_minimum_required(VERSION 3.26)
project(AdvancedC)

set(CMAKE_CXX_STANDARD 23)

add_executable(AdvancedC src/main.cpp
        src/Krankenhaus.cpp
        src/Krankenhaus.h
        src/Personen/Patient.cpp
        src/Personen/Patient.h
        src/Personen/Angestellter.cpp
        src/Personen/Angestellter.h
        src/Terminkalender.cpp
        src/Terminkalender.h
        main.cpp
        src/Personen/Patient.h
        src/Krankenhaus.h
        src/Personen/Angestellter.h
        src/Adresse.cpp
        src/Adresse.h
        src/Behandlungen/Behandlung.cpp
        src/Behandlungen/Behandlung.h
        src/BehandlungTypen.h)
