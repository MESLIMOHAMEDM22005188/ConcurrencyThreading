#include "ElevatorProblem.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <sstream>
#include <chrono>
#include <vector>

namespace ElevatorProblem {

    constexpr int MAX_FLOOR = 10;
    int currentFloor = 0;
    bool moving = false;

    std::mutex mtx;
    std::condition_variable cv;
    std::queue<int> requests;
    std::vector<std::string> logMessages;

    void log(const std::string& msg) {
        std::lock_guard<std::mutex> lock(mtx);
        logMessages.push_back(msg);
    }

    void elevator() {
        std::unique_lock<std::mutex> lock(mtx);
        while (true) {
            while (requests.empty()) {
                log("Ascenseur attend une demande...");
                cv.wait(lock);
            }

            int floor = requests.front();
            requests.pop();
            moving = true;
            log("Ascenseur se déplace vers l'étage " + std::to_string(floor));
            lock.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(500 + abs(floor - currentFloor) * 200));
            currentFloor = floor;

            lock.lock();
            log("Ascenseur arrivé à l'étage " + std::to_string(currentFloor));
            moving = false;
        }
    }

    void passenger(int id, int targetFloor) {
        std::unique_lock<std::mutex> lock(mtx);
        log("Passager #" + std::to_string(id) + " demande l'étage " + std::to_string(targetFloor));
        requests.push(targetFloor);
        cv.notify_one();
    }

    void runElevatorProblem() {
        logMessages.clear();
        currentFloor = 0;
        moving = false;

        std::thread elevatorThread(elevator);

        std::vector<std::thread> passengers;
        passengers.emplace_back(passenger, 1, 5);
        passengers.emplace_back(passenger, 2, 8);
        passengers.emplace_back(passenger, 3, 2);
        passengers.emplace_back(passenger, 4, 10);

        for (auto& t : passengers) t.join();

        elevatorThread.detach();  // Pas de terminaison propre
    }

    std::string generateElevatorHTML() {
        std::ostringstream html;
        html << "<html><body><h1>Problème de l'Ascenseur</h1><ul>";
        for (const auto& line : logMessages) {
            html << "<li>" << line << "</li>";
        }
        html << "</ul></body></html>";
        return html.str();
    }

}

