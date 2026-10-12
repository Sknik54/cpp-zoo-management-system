cmake_minimum_required(VERSION 4.0)
project(Zoo_Projekt_5)

set(CMAKE_CXX_STANDARD 20)

add_executable(Zoo_Projekt_5 main.cpp
        parameter_reader.h
        enclosure.cpp
        enclosure.h
        animal.cpp
        animal.h
        assignment.cpp
        assignment.h
        befehle.cpp
        befehle.h
        spezie.cpp
        spezie.h
        zooio.cpp
        zooio.h
        errorfall.h
        zoodb.cpp
        zoodb.h
)
