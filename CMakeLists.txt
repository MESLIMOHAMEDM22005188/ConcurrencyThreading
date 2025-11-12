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
