cmake_minimum_required(VERSION 3.31)
project(concurency)

set(CMAKE_CXX_STANDARD 20)

add_executable(concurency_app main.cpp
        WorkerConcurrency.cpp
        LoggerSync.cpp
        LoggerSync.hpp
        BenchmarkPerformence.cpp
        BenchmarkPerformence.hpp
        BarberProblem.hpp
        BarberProblem.cpp
        ElevatorProblem.cpp
        ElevatorProblem.hpp
        BuffetProblem.cpp
        BuffetProblem.hpp
        LightouseProblem.cpp
        LightouseProblem.hpp
)

