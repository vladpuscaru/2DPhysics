cmake_minimum_required(VERSION 3.14)
project(physics_engine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES src/main.cpp
        src/OVTVector/OVTVector.cpp
        src/OVTVector/OVTVector.h
        src/Game/Game.cpp
        src/Game/Game.h
        src/OVTMath/OVTMath.cpp
        src/OVTMath/OVTMath.h)
add_executable(physics_engine ${SOURCE_FILES})

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(physics_engine sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

