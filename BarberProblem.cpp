#include "BarberProblem.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <sstream>
#include <chrono>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>

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
    std::map<int, bool> served; // false = en attente, true = servi

    static std::chrono::steady_clock::time_point startTime;

    static long long now_ms() {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
    }

    void debugLog(const std::string& msg) {
        std::ostringstream oss;
        oss << "[" << std::setw(4) << now_ms() << " ms] " << msg;
        {
            std::lock_guard<std::mutex> lock(mtx);
            logMessages.push_back(oss.str());
        }
        std::cout << oss.str() << std::endl;
    }

    void barber() {
        debugLog("Barbier: thread demarre");
        std::unique_lock<std::mutex> lock(mtx);

        while (shopOpen || !customerQueue.empty()) {
            if (customerQueue.empty()) {
                if (!shopOpen) break;
                debugLog("Barbier dort car pas de clients");
                barberSleeping = true;

                cvBarber.wait(lock, [] { return !customerQueue.empty() || !shopOpen; });
                barberSleeping = false;
            }

            if (!customerQueue.empty()) {
                int customerId = customerQueue.front();
                customerQueue.pop();
                waitingCustomers--;

                debugLog("Barbier coupe les cheveux du client #" + std::to_string(customerId));
                lock.unlock();

                std::this_thread::sleep_for(std::chrono::milliseconds(700)); // simulation coupe

                lock.lock();
                served[customerId] = true; // marque comme servi
                cvCustomer.notify_all();
                debugLog("Client #" + std::to_string(customerId) + " est parti");
            }
        }

        debugLog("Barbier ferme le salon et rentre chez lui 💤");
    }

    void customer(int id) {
        debugLog("Client #" + std::to_string(id) + " thread demarre");

        std::unique_lock<std::mutex> lock(mtx);
        if (!shopOpen) {
            debugLog("Client #" + std::to_string(id) + " arrive mais le salon est ferme");
            return;
        }

        if (waitingCustomers == MAX_CHAIRS) {
            debugLog("Client #" + std::to_string(id) + " part car pas de place");
            return;
        }

        waitingCustomers++;
        customerQueue.push(id);
        served[id] = false;
        debugLog("Client #" + std::to_string(id) + " s'assoit (attente=" + std::to_string(waitingCustomers) + ")");

        if (barberSleeping) {
            debugLog("Client #" + std::to_string(id) + " reveille le barbier");
            cvBarber.notify_one();
        }

        debugLog("Client #" + std::to_string(id) + " attend son tour");
        cvCustomer.wait(lock, [&] { return served[id]; });

        debugLog("Client #" + std::to_string(id) + " a fini et quitte le salon");
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
            while (!customerQueue.empty()) customerQueue.pop();
        }

        debugLog("runBarberProblem: demarrage simulation");
        std::thread barberThread(barber);

        std::vector<std::thread> customers;
        for (int i = 1; i <= 8; ++i) {
            debugLog("runBarberProblem: creation client #" + std::to_string(i));
            customers.emplace_back(customer, i);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        for (auto &t : customers)
            if (t.joinable()) t.join();

        {
            std::lock_guard<std::mutex> lock(mtx);
            shopOpen = false;
            cvBarber.notify_all();
            cvCustomer.notify_all();
        }

        if (barberThread.joinable())
            barberThread.join();

        debugLog("runBarberProblem: simulation terminee");
    }

    void printLogs() {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "\n=== Journal du Barbier Dormant ===" << std::endl;
        for (const auto &line : logMessages)
            std::cout << line << std::endl;
        std::cout << "==================================" << std::endl;
    }

    std::string generateBarberHTML() {
        std::lock_guard<std::mutex> lock(mtx);
        std::ostringstream html;
        html << "<html><body><h1>Problème du Barbier Dormant</h1><ul>";
        for (const auto &line : logMessages)
            html << "<li>" << line << "</li>";
        html << "</ul></body></html>";
        return html.str();
    }


} // namespace BarberProblem
