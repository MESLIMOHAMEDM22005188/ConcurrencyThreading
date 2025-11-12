<<<<<<< HEAD
cmake_minimum_required(VERSION 3.26)
project(concurency_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Liste des fichiers sources de ton projet
add_executable(concurency_app
        main.cpp
        WorkerConcurrency.cpp
        LoggerSync.cpp
        BenchmarkPerformence.cpp
        BarberProblem.cpp
        ElevatorProblem.cpp
        BuffetProblem.cpp
        LightouseProblem.cpp
)

# Sous Windows, forcer le mode console (corrige WinMain)
if (WIN32)
    set_target_properties(concurency_app PROPERTIES LINK_FLAGS "-Wl,-subsystem,console")
endif()
=======
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

>>>>>>> d7828240d4531925dbd6db04f464d848ad9d7580
