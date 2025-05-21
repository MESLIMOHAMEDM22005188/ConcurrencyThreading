#include "BenchmarkPerformence.hpp"
#include <chrono>
#include <iostream>

namespace BenchmarkPerformance {

    double runBenchmark() {
        auto start = std::chrono::high_resolution_clock::now();
        long long sum = 0;
        for (int i = 0; i < 10000000; ++i) {
            sum += i;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        return diff.count();
    }

    void printPerformance(double seconds) {
        std::cout << "Benchmark Performance :\n";
        std::cout << " Temps d'exécution du calcul : " << seconds << " secondes\n";
    }
}
