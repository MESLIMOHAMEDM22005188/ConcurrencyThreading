#include "BarberProblem.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <sstream>
#include <chrono>

namespace BarberProblem {

    constexpr int MAX_CHAIRS = 3;
    int waitingCustomers = 0;
    bool barberSleeping = false;

    std::mutex mtx;
    std::condition_variable cvBarber;
    std::condition_variable cvCustomer;

    std::queue<int> customerQueue;
    std::vector<std::string> logMessages;

    void log(const std::string& msg) {
        std::lock_guard<std::mutex> lock(mtx);
        logMessages.push_back(msg);
    }

    void barber() {
        std::unique_lock<std::mutex> lock(mtx);
        while (true) {
            while (customerQueue.empty()) {
                log("Barbier dort car pas de clients");
                barberSleeping = true;
                cvBarber.wait(lock);  // Attend un client
            }
            barberSleeping = false;
            int customerId = customerQueue.front();
            customerQueue.pop();
            waitingCustomers--;
            log("Barbier coupe les cheveux du client #" + std::to_string(customerId));
            lock.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(700)); // coupe les cheveux

            lock.lock();
            cvCustomer.notify_all();  // Réveille clients si besoin
        }
    }

    void customer(int id) {
        std::unique_lock<std::mutex> lock(mtx);
        if (waitingCustomers == MAX_CHAIRS) {
            log("Client #" + std::to_string(id) + " part, pas de place");
            return;  // Pas de place, client part
        }

        waitingCustomers++;
        customerQueue.push(id);
        log("Client #" + std::to_string(id) + " attend");

        if (barberSleeping) {
            cvBarber.notify_one(); // Réveille barbier
        }

        cvCustomer.wait(lock, [&] { return customerQueue.front() != id; });
        log("Client #" + std::to_string(id) + " a fini chez le barbier");
    }

    void runBarberProblem() {
        logMessages.clear();
        waitingCustomers = 0;
        barberSleeping = false;

        std::thread barberThread(barber);

        std::vector<std::thread> customers;
        for (int i = 1; i <= 8; ++i) {
            customers.emplace_back(customer, i);
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }

        for (auto& t : customers) t.join();

        // Le barbier ne va pas s'arrêter ici car boucle infinie, on force fin (en vrai on ferait mieux)
        barberThread.detach();
    }

    std::string generateBarberHTML() {
        std::ostringstream html;
        html << "<html><body><h1>Problème du Barbier Dormant</h1><ul>";
        for (const auto& line : logMessages) {
            html << "<li>" << line << "</li>";
        }
        html << "</ul></body></html>";
        return html.str();
    }

}

