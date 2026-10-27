#include "BuffetProblem.hpp"

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace BuffetProblem {

    constexpr int MAX_DISHES = 5;
    int dishesAvailable = MAX_DISHES;

    std::mutex mtx;
    std::condition_variable cv;
    std::vector<std::string> logMessages;

    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        logMessages.push_back(message);
    }

    void serveDish(int customerId) {
        std::unique_lock<std::mutex> lock(mtx);

        while (dishesAvailable == 0) {
            log("Customer #" + std::to_string(customerId) + " is waiting for the buffet to be replenished");
            cv.wait(lock);
        }

        --dishesAvailable;
        log("Customer #" + std::to_string(customerId) + " takes a dish; dishes remaining: " +
            std::to_string(dishesAvailable));
        lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        lock.lock();
        log("Customer #" + std::to_string(customerId) + " has finished eating");
    }

    void replenish() {
        std::unique_lock<std::mutex> lock(mtx);

        while (true) {
            if (dishesAvailable == 0) {
                log("Replenishing the buffet...");
                dishesAvailable = MAX_DISHES;
                cv.notify_all();
            }

            lock.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            lock.lock();
        }
    }

    void runBuffetProblem() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            logMessages.clear();
            dishesAvailable = MAX_DISHES;
        }

        std::thread replenisher(replenish);

        std::vector<std::thread> customers;
        for (int id = 1; id <= 10; ++id) {
            customers.emplace_back(serveDish, id);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        for (auto& thread : customers) {
            thread.join();
        }

        // This demonstration thread remains active while the program runs.
        replenisher.detach();
    }

    std::string generateBuffetHTML() {
        std::lock_guard<std::mutex> lock(mtx);
        std::ostringstream html;
        html << "<html><body><h1>Buffet Problem</h1><ul>";
        for (const auto& line : logMessages) {
            html << "<li>" << line << "</li>";
        }
        html << "</ul></body></html>";
        return html.str();
    }

} // namespace BuffetProblem
