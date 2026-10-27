#include "ElevatorProblem.hpp"

#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace ElevatorProblem {

    constexpr int MAX_FLOOR = 10;
    int currentFloor = 0;
    bool moving = false;

    std::mutex mtx;
    std::condition_variable cv;
    std::queue<int> requests;
    std::vector<std::string> logMessages;

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        logMessages.push_back(message);
    }

    void elevator() {
        std::unique_lock<std::mutex> lock(mtx);

        while (true) {
            while (requests.empty()) {
                log("Elevator is waiting for a request...");
                cv.wait(lock);
            }

            const int targetFloor = requests.front();
            requests.pop();
            moving = true;

            const int distance = std::abs(targetFloor - currentFloor);
            log("Elevator is moving to floor " + std::to_string(targetFloor));
            lock.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(500 + distance * 200));
            lock.lock();

            currentFloor = targetFloor;
            log("Elevator has arrived at floor " + std::to_string(currentFloor));
            moving = false;
        }
    }

    void passenger(int id, int targetFloor) {
        std::lock_guard<std::mutex> lock(mtx);
        log("Passenger #" + std::to_string(id) + " requested floor " + std::to_string(targetFloor));
        requests.push(targetFloor);
        cv.notify_one();
    }

    void runElevatorProblem() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            logMessages.clear();
            while (!requests.empty()) {
                requests.pop();
            }
            currentFloor = 0;
            moving = false;
        }

        std::thread elevatorThread(elevator);

        std::vector<std::thread> passengers;
        passengers.emplace_back(passenger, 1, 5);
        passengers.emplace_back(passenger, 2, 8);
        passengers.emplace_back(passenger, 3, 2);
        passengers.emplace_back(passenger, 4, 10);

        for (auto& thread : passengers) {
            thread.join();
        }

        // This is a demonstration thread that remains active while the program runs.
        elevatorThread.detach();
    }

    std::string generateElevatorHTML() {
        std::lock_guard<std::mutex> lock(mtx);
        std::ostringstream html;
        html << "<html><body><h1>Elevator Problem</h1><ul>";
        for (const auto& line : logMessages) {
            html << "<li>" << line << "</li>";
        }
        html << "</ul></body></html>";
        return html.str();
    }

} // namespace ElevatorProblem
