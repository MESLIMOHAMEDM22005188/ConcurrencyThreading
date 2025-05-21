#include "LightouseProblem.hpp"
#include <thread>
#include <mutex>
#include <vector>
#include <sstream>
#include <chrono>

namespace LighthouseProblem {

    std::mutex mtx;
    bool lightOn = false;
    std::vector<std::string> logMessages;

    void log(const std::string& msg) {
        std::lock_guard<std::mutex> lock(mtx);
        logMessages.push_back(msg);
    }

    void lighthouse() {
        while (true) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                lightOn = !lightOn;
                log("Phare " + std::string(lightOn ? "allumé" : "éteint"));
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void ship(int id) {
        for (int i = 0; i < 3; ++i) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (lightOn) {
                    log("Navire #" + std::to_string(id) + " passe en toute sécurité");
                } else {
                    log("Navire #" + std::to_string(id) + " attend que le phare s'allume");
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
        }
    }

    void runLighthouseProblem() {
        logMessages.clear();
        lightOn = false;

        std::thread lightThread(lighthouse);

        std::vector<std::thread> ships;
        for (int i = 1; i <= 5; ++i) {
            ships.emplace_back(ship, i);
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }

        for (auto& t : ships) t.join();
        lightThread.detach();
    }

    std::string generateLighthouseHTML() {
        std::ostringstream html;
        html << "<html><body><h1>Problème du Phare</h1><ul>";
        for (const auto& line : logMessages) {
            html << "<li>" << line << "</li>";
        }
        html << "</ul></body></html>";
        return html.str();
    }

}

