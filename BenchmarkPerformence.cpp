#include "BenchmarkPerformence.hpp"

#include <chrono>
#include <iostream>

namespace BenchmarkPerformance {

    double runBenchmark() {
        const auto start = std::chrono::high_resolution_clock::now();
        volatile long long sum = 0;

        for (int i = 0; i < 10'000'000; ++i) {
            sum += i;
        }

        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> elapsed = end - start;
        return elapsed.count();
    }

    void printPerformance(double seconds) {
        std::cout << "Performance benchmark:" << std::endl;
        std::cout << "Calculation runtime: " << seconds << " seconds" << std::endl;
    }

} // namespace BenchmarkPerformance
