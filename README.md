# C++ Concurrency Playground

A hands-on C++ project for exploring concurrency, thread synchronization, and performance through small, interactive command-line demonstrations.

The examples use C++20 and the standard threading library.

## Concepts covered

1. **Concurrent execution** — Split an integer-summing task across multiple threads.
2. **Thread-safe logging** — Protect shared log data with a mutex.
3. **Performance benchmarking** — Measure the runtime of a computationally intensive loop.
4. **The sleeping barber problem** — Model coordination between a barber and waiting customers.
5. **The elevator problem** — Simulate concurrent floor requests.
6. **The buffet problem** — Explore concurrent consumption, waiting, and replenishment.
7. **The lighthouse problem** — Simulate synchronization between a lighthouse and ships.

## Project structure

- `main.cpp`: Interactive menu and application entry point.
- `WorkerConcurrency.hpp/.cpp`: Parallel computation example.
- `LoggerSync.hpp/.cpp`: Thread-safe logging using a mutex.
- `BenchmarkPerformance.hpp/.cpp`: Execution-time benchmark.
- `BarberProblem.hpp/.cpp`: Sleeping barber simulation.
- `ElevatorProblem.hpp/.cpp`: Elevator request simulation.
- `BuffetProblem.hpp/.cpp`: Shared buffet simulation.
- `LighthouseProblem.hpp/.cpp`: Lighthouse and ship simulation.
- `CMakeLists.txt`: CMake build configuration.

## Requirements

- A C++20-compatible compiler
- CMake 3.26 or later

## Build

From the repository root:

```bash
cmake -S . -B build
cmake --build build
```

Run the executable generated in the `build` directory. The exact executable path depends on your operating system and generator.

## Learning goals

This project is intended to make concurrency concepts easier to understand by showing how threads run, how shared state is protected, and how coordination problems can be modelled.

## Notes

Some simulations emit HTML-formatted output as a string; they do not necessarily write an HTML file automatically.
