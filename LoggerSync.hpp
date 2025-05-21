#ifndef LOGGERSYNC_HPP
#define LOGGERSYNC_HPP

#include <vector>
#include <string>

namespace LoggerSync {
    void runSafeLogging(std::vector<std::string>& logMessages);
    void printLogs(const std::vector<std::string>& logs);
}

#endif // LOGGERSYNC_HPP

