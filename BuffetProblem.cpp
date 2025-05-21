#include "BuffetProblem.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sstream>
#include <vector>
#include <chrono>

namespace BuffetProblem {

    constexpr int MAX_DISHES = 5;
    int dishesAvailable = MAX_DISHES;

    std::mutex mtx;
    std::condition_variable cv;
    std::vector<std::string> logMessages;

    void log(const std::string& msg) {
        std::lock_guard<std::mutex> lock(mtx);
        logMessages.push_back(msg);
    }

    void serveDish(int customerId) {
        std::unique_lock<std::mutex> lock(mtx);
        while (dishesAvailable == 0) {
            log("Client #" + std::to_string(customerId) + " attend la réapprovisionnement");
            cv.wait(lock);
        }
        dishesAvailable--;
        log("Client #" + std::to_string(customerId) + " prend un plat, plats restants: " + std::to_string(dishesAvailable));
        lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        lock.lock();
        log("Client #" + std::to_string(customerId) + " a fini de manger");
    }

    void replenish() {
        std::unique_lock<std::mutex> lock(mtx);
        while (true) {
            if (dishesAvailable == 0) {
                log("Réapprovisionnement du buffet...");
                dishesAvailable = MAX_DISHES;
                cv.notify_all();
            }
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            lock.lock();
        }
    }

    void runBuffetProblem() {
        logMessages.clear();
        dishesAvailable = MAX_DISHES;

        std::thread replenisher(replenish);

        std::vector<std::thread> customers;
        for (int i = 1; i <= 10; ++i) {
            customers.emplace_back(serveDish, i);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        for (auto& t : customers) t.join();
        replenisher.detach();
    }

    std::string generateBuffetHTML() {
        std::ostringstream html;
        html << "<html><body><h1>Problème du Buffet</h1><ul>";
        for (const auto& line : logMessages) {
            html << "<li>" << line << "</li>";
        }
        html << "</ul></body></html>";
        return html.str();
    }
}
