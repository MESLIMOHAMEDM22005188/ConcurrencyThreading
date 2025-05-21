#include "LoggerSync.hpp"
#include <thread>
#include <mutex>
#include <iostream>

namespace LoggerSync {

    std::mutex logMutex;

    void safeLog(const std::string& msg, std::vector<std::string>& logs) {
        std::lock_guard<std::mutex> lock(logMutex);
        logs.push_back(msg);
    }

    void runSafeLogging(std::vector<std::string>& logMessages) {
        std::thread t1(safeLog, "Thread A a écrit ce log", std::ref(logMessages));
        std::thread t2(safeLog, "Thread B a écrit ce log", std::ref(logMessages));
        t1.join();
        t2.join();
    }

    void printLogs(const std::vector<std::string>& logs) {
        std::cout << "Logs Synchronisés (avec protection mutex) :\n";
        for (const auto& entry : logs) {
            std::cout << " - " << entry << '\n';
        }
    }
}

