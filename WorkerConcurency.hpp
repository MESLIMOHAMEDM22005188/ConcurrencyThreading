#ifndef WORKERCONCURRENCY_HPP
#define WORKERCONCURRENCY_HPP

#include <vector>
#include <string>

namespace WorkerConcurrency {
    void executeAdditionTask(std::vector<int>& results);
    void printResults(const std::vector<int>& results);
}

#endif // WORKERCONCURRENCY_HPP

