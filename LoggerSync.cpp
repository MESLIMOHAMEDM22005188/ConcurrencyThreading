#include "LoggerSync.hpp"

#include <iostream>
#include <mutex>
#include <thread>

namespace LoggerSync {

    std::mutex logMutex;

    void safeLog(const std::string& message, std::vector<std::string>& logs) {
        std::lock_guard<std::mutex> lock(logMutex);
        logs.push_back(message);
    }

    void runSafeLogging(std::vector<std::string>& logMessages) {
        std::thread firstThread(safeLog, "Thread A wrote this log entry", std::ref(logMessages));
        std::thread secondThread(safeLog, "Thread B wrote this log entry", std::ref(logMessages));
        firstThread.join();
        secondThread.join();
    }

    void printLogs(const std::vector<std::string>& logs) {
        std::cout << "Synchronized logs (protected by a mutex):" << std::endl;
        for (const auto& entry : logs) {
            std::cout << " - " << entry << std::endl;
        }
    }

} // namespace LoggerSync
