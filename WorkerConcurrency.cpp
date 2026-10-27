#include "WorkerConcurrency.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

namespace WorkerConcurrency {

    // Calculate the sum of an inclusive integer range.
    void addRange(int start, int end, int& result) {
        result = 0;
        for (int value = start; value <= end; ++value) {
            result += value;
        }
    }

    // Split the addition task across two threads and measure its runtime.
    void executeAdditionTask(std::vector<int>& results) {
        int firstResult = 0;
        int secondResult = 0;

        std::cout << "\n=== EXERCISE OVERVIEW ===\n";
        std::cout << "We want to add all integers from 1 to 10,000.\n";
        std::cout << "Instead of running the calculation sequentially on one thread,\n";
        std::cout << "we split it into two parts and execute them concurrently.\n";
        std::cout << "Thread 1: adds the integers from 1 to 5,000.\n";
        std::cout << "Thread 2: adds the integers from 5,001 to 10,000.\n";
        std::cout << "This illustrates concurrency: multiple tasks make progress during overlapping periods.\n\n";
        std::cout << "Creating and starting both threads...\n";

        const auto startTime = std::chrono::high_resolution_clock::now();

        std::thread firstThread(addRange, 1, 5000, std::ref(firstResult));
        std::thread secondThread(addRange, 5001, 10000, std::ref(secondResult));

        firstThread.join();
        secondThread.join();

        const auto endTime = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> elapsed = endTime - startTime;

        std::cout << "Both threads have completed their work.\n";
        std::cout << "Total execution time: " << elapsed.count() << " seconds\n\n";

        results = {firstResult, secondResult};
    }

    // Display the partial sums and their combined result.
    void printResults(const std::vector<int>& results) {
        std::cout << "=== RESULTS ===\n";

        for (std::size_t index = 0; index < results.size(); ++index) {
            std::cout << "Thread " << (index + 1)
                      << ": partial sum = " << results[index] << '\n';
        }

        if (results.size() >= 2) {
            std::cout << "Combined total: " << (results[0] + results[1]) << "\n\n";
        }

        std::cout << "Why it matters:\n";
        std::cout << "Splitting work across threads can help use multi-core processors.\n";
        std::cout << "Concurrency is a key concept in systems programming, servers, and simulations.\n";
    }

} // namespace WorkerConcurrency
