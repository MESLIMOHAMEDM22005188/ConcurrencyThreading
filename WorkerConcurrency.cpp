#include "WorkerConcurrency.hpp"
#include <thread>
#include <iostream>

namespace WorkerConcurrency {

    void addRange(int start, int end, int& result) {
        result = 0;
        for (int i = start; i <= end; ++i) {
            result += i;
        }
    }

    void executeAdditionTask(std::vector<int>& results) {
        int r1 = 0, r2 = 0;
        std::thread t1(addRange, 1, 5000, std::ref(r1));
        std::thread t2(addRange, 5001, 10000, std::ref(r2));
        t1.join();
        t2.join();
        results = { r1, r2 };
    }

    void printResults(const std::vector<int>& results) {
        std::cout << "Résultat Concurrence (addition parallèle) :\n";
        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << " Thread " << (i + 1) << " → Somme: " << results[i] << '\n';
        }
    }
}

