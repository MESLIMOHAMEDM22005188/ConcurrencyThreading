#include "LighthouseProblem.hpp"

#include <chrono>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace LighthouseProblem {

    std::mutex mtx;
    bool lightOn = false;
    std::vector<std::string> logMessages;

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        logMessages.push_back(message);
    }

    void lighthouse() {
        while (true) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                lightOn = !lightOn;
                log("Lighthouse light " + std::string(lightOn ? "turned on" : "turned off"));
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void ship(int id) {
        for (int attempt = 0; attempt < 3; ++attempt) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (lightOn) {
                    log("Ship #" + std::to_string(id) + " passes safely");
                } else {
                    log("Ship #" + std::to_string(id) + " is waiting for the lighthouse to turn on");
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(700));
        }
    }

    void runLighthouseProblem() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            logMessages.clear();
            lightOn = false;
        }

        std::thread lightThread(lighthouse);

        std::vector<std::thread> ships;
        for (int id = 1; id <= 5; ++id) {
            ships.emplace_back(ship, id);
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }

        for (auto& thread : ships) {
            thread.join();
        }

        // This demonstration thread remains active while the program runs.
        lightThread.detach();
    }

    std::string generateLighthouseHTML() {
        std::lock_guard<std::mutex> lock(mtx);
        std::ostringstream html;
        html << "<html><body><h1>Lighthouse Problem</h1><ul>";
        for (const auto& line : logMessages) {
            html << "<li>" << line << "</li>";
        }
        html << "</ul></body></html>";
        return html.str();
    }

} // namespace LighthouseProblem
