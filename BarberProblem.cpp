#include "BarberProblem.hpp"

#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace BarberProblem {

    constexpr int MAX_CHAIRS = 3;
    int waitingCustomers = 0;
    bool barberSleeping = false;
    bool shopOpen = true;

    std::mutex mtx;
    std::condition_variable cvBarber;
    std::condition_variable cvCustomer;

    std::queue<int> customerQueue;
    std::vector<std::string> logMessages;
    std::map<int, bool> served; // false = waiting, true = served

    static std::chrono::steady_clock::time_point startTime;

    static long long now_ms() {
        const auto now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
    }

    void debugLog(const std::string& message) {
        std::ostringstream stream;
        stream << "[" << std::setw(4) << now_ms() << " ms] " << message;
        {
            std::lock_guard<std::mutex> lock(mtx);
            logMessages.push_back(stream.str());
        }
        std::cout << stream.str() << std::endl;
    }

    void barber() {
        debugLog("Barber: thread started");
        std::unique_lock<std::mutex> lock(mtx);

        while (shopOpen || !customerQueue.empty()) {
            if (customerQueue.empty()) {
                if (!shopOpen) {
                    break;
                }

                debugLog("Barber is sleeping because there are no customers");
                barberSleeping = true;
                cvBarber.wait(lock, [] { return !customerQueue.empty() || !shopOpen; });
                barberSleeping = false;
            }

            if (!customerQueue.empty()) {
                const int customerId = customerQueue.front();
                customerQueue.pop();
                waitingCustomers--;

                debugLog("Barber is cutting the hair of customer #" + std::to_string(customerId));
                lock.unlock();

                std::this_thread::sleep_for(std::chrono::milliseconds(700)); // Simulate a haircut.

                lock.lock();
                served[customerId] = true;
                cvCustomer.notify_all();
                debugLog("Customer #" + std::to_string(customerId) + " has been served");
            }
        }

        debugLog("Barber closes the shop and goes home");
    }

    void customer(int id) {
        debugLog("Customer #" + std::to_string(id) + ": thread started");

        std::unique_lock<std::mutex> lock(mtx);
        if (!shopOpen) {
            debugLog("Customer #" + std::to_string(id) + " arrives, but the shop is closed");
            return;
        }

        if (waitingCustomers == MAX_CHAIRS) {
            debugLog("Customer #" + std::to_string(id) + " leaves because there is no waiting chair available");
            return;
        }

        waitingCustomers++;
        customerQueue.push(id);
        served[id] = false;
        debugLog("Customer #" + std::to_string(id) + " takes a seat (waiting=" +
                 std::to_string(waitingCustomers) + ")");

        if (barberSleeping) {
            debugLog("Customer #" + std::to_string(id) + " wakes up the barber");
            cvBarber.notify_one();
        }

        debugLog("Customer #" + std::to_string(id) + " is waiting for their turn");
        cvCustomer.wait(lock, [&] { return served[id]; });
        debugLog("Customer #" + std::to_string(id) + " has finished and leaves the shop");
    }

    void runBarberProblem() {
        startTime = std::chrono::steady_clock::now();
        {
            std::lock_guard<std::mutex> lock(mtx);
            logMessages.clear();
            waitingCustomers = 0;
            barberSleeping = false;
            shopOpen = true;
            served.clear();
            while (!customerQueue.empty()) {
                customerQueue.pop();
            }
        }

        debugLog("runBarberProblem: starting simulation");
        std::thread barberThread(barber);

        std::vector<std::thread> customers;
        for (int id = 1; id <= 8; ++id) {
            debugLog("runBarberProblem: creating customer #" + std::to_string(id));
            customers.emplace_back(customer, id);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        for (auto& thread : customers) {
            if (thread.joinable()) {
                thread.join();
            }
        }

        {
            std::lock_guard<std::mutex> lock(mtx);
            shopOpen = false;
            cvBarber.notify_all();
            cvCustomer.notify_all();
        }

        if (barberThread.joinable()) {
            barberThread.join();
        }

        debugLog("runBarberProblem: simulation completed");
    }

    void printLogs() {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "\n=== Sleeping Barber Log ===" << std::endl;
        for (const auto& line : logMessages) {
            std::cout << line << std::endl;
        }
        std::cout << "============================" << std::endl;
    }

    std::string generateBarberHTML() {
        std::lock_guard<std::mutex> lock(mtx);
        std::ostringstream html;
        html << "<html><body><h1>Sleeping Barber Problem</h1><ul>";
        for (const auto& line : logMessages) {
            html << "<li>" << line << "</li>";
        }
        html << "</ul></body></html>";
        return html.str();
    }

} // namespace BarberProblem
