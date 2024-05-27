cmake_minimum_required(VERSION 3.10)
project(MonteCarlo)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        MonteCarlo 
        main.cpp
        Normal.h
        Payoff.cpp
        MonteCarlo.cpp)