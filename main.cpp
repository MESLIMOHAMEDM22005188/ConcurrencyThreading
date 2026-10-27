#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "WorkerConcurrency.hpp"
#include "LoggerSync.hpp"
#include "BenchmarkPerformance.hpp"
#include "BarberProblem.hpp"
#include "ElevatorProblem.hpp"
#include "BuffetProblem.hpp"
#include "LighthouseProblem.hpp"

int main() {
    bool keepRunning = true;

    while (keepRunning) {
        std::cout << "\n==============================================\n";
        std::cout << "Welcome to the C++ Concurrency Simulator!" << std::endl;
        std::cout << "Choose a concept to explore:" << std::endl;
        std::cout << "==============================================\n\n";

        std::cout << "1 - Concurrency (multithreading)\n"
                  << "    Run a calculation in parallel across two threads.\n\n";

        std::cout << "2 - Synchronization (mutex-protected logging)\n"
                  << "    Append messages to a shared vector from multiple threads.\n\n";

        std::cout << "3 - Performance (simple benchmark)\n"
                  << "    Measure the runtime of an intensive addition loop.\n\n";

        std::cout << "4 - Sleeping Barber Problem\n"
                  << "    Simulate a classic thread-synchronization problem.\n\n";

        std::cout << "5 - Elevator Problem\n"
                  << "    Handle concurrent floor requests.\n\n";

        std::cout << "6 - Buffet Problem\n"
                  << "    Simulate consumption and replenishment with waiting.\n\n";

        std::cout << "7 - Lighthouse Problem\n"
                  << "    Simulate synchronization between a lighthouse and ships.\n\n";

        int choice = 0;
        while (true) {
            std::cout << "Enter a number between 1 and 7: ";
            if (!(std::cin >> choice)) {
                // Recover from invalid input and clear the input buffer.
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please try again." << std::endl;
                continue;
            }

            if (choice >= 1 && choice <= 7) {
                break;
            }

            std::cout << "Number out of range. Please try again." << std::endl;
        }

        std::cout << "\n==============================================\n";

        switch (choice) {
            case 1: {
                std::vector<int> results;
                std::cout << "\nConcurrency demonstration:" << std::endl;
                WorkerConcurrency::executeAdditionTask(results);
                WorkerConcurrency::printResults(results);
                break;
            }
            case 2: {
                std::vector<std::string> logs;
                std::cout << "\nMutex synchronization test:" << std::endl;
                LoggerSync::runSafeLogging(logs);
                LoggerSync::printLogs(logs);
                break;
            }
            case 3: {
                std::cout << "\nPerformance benchmark:" << std::endl;
                const double elapsedSeconds = BenchmarkPerformance::runBenchmark();
                BenchmarkPerformance::printPerformance(elapsedSeconds);
                break;
            }
            case 4: {
                std::cout << "\nSleeping Barber Problem simulation:" << std::endl;
                BarberProblem::runBarberProblem();
                BarberProblem::printLogs();
                break;
            }
            case 5: {
                std::cout << "\nElevator Problem simulation:" << std::endl;
                ElevatorProblem::runElevatorProblem();
                std::cout << ElevatorProblem::generateElevatorHTML() << std::endl;
                break;
            }
            case 6: {
                std::cout << "\nBuffet Problem simulation:" << std::endl;
                BuffetProblem::runBuffetProblem();
                std::cout << BuffetProblem::generateBuffetHTML() << std::endl;
                break;
            }
            case 7: {
                std::cout << "\nLighthouse Problem simulation:" << std::endl;
                LighthouseProblem::runLighthouseProblem();
                std::cout << LighthouseProblem::generateLighthouseHTML() << std::endl;
                break;
            }
            default:
                break;
        }

        std::cout << "\n==============================================\n";
        std::cout << "Would you like to run another example? (y/n): ";
        char answer{};
        std::cin >> answer;

        if (answer != 'y' && answer != 'Y') {
            keepRunning = false;
        }
    }

    std::cout << "\nThank you for using the simulator. Goodbye!" << std::endl;
    return 0;
}
