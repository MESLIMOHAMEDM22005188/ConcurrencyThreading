#ifndef LOGGER_SYNC_HPP
#define LOGGER_SYNC_HPP

#include <string>
#include <vector>

namespace LoggerSync {
    void runSafeLogging(std::vector<std::string>& logMessages);
    void printLogs(const std::vector<std::string>& logs);
}

#endif // LOGGER_SYNC_HPP
