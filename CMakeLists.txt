cmake_minimum_required(VERSION 3.26)

project(CppConcurrencyPlayground VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(concurrency_playground
    main.cpp
    WorkerConcurrency.cpp
    LoggerSync.cpp
    BenchmarkPerformance.cpp
    BarberProblem.cpp
    ElevatorProblem.cpp
    BuffetProblem.cpp
    LighthouseProblem.cpp
)

target_link_libraries(concurrency_playground PRIVATE Threads::Threads)

if (MSVC)
    target_compile_options(concurrency_playground PRIVATE /W4)
else()
    target_compile_options(concurrency_playground PRIVATE -Wall -Wextra -Wpedantic)
endif()
