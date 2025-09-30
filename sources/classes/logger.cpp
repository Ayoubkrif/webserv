#include "Logger.hpp"

// Logger implementation matches includes/Logger.hpp where file_ is static std::ofstream
// The static members are defined elsewhere in the implementation unit that provides them.

LogPrio Logger::prio = DEBUG;
L_State Logger::state = ON;
std::ofstream Logger::file_;
std::string Logger::file_name;
std::map<LogPrio, std::pair<std::string, std::ostream*> > Logger::levels;

Logger::Logger(const std::string& filename) {

    Logger::initLevels();

    if (!filename.empty()) {
        file_name = filename;
        if (!file_.is_open()) {
            file_.open(file_name.c_str(), std::ios::app);
        }
    }
}

Logger::~Logger() {
    // Do not close static file_ here; leave it open for program lifetime.
}

Logger::Logger(const Logger& other) {
    // No per-instance state to copy; file_ is static
    (void)other;
}

Logger& Logger::operator=(const Logger& other) {
    (void)other;
    return *this;
}

void Logger::initLevels() {
    levels.clear();
    levels.insert(std::make_pair(DEBUG,   std::make_pair(std::string("DEBUG"), &std::cout)));
    levels.insert(std::make_pair(INFO,    std::make_pair(std::string("INFO"),  &std::cout)));
    levels.insert(std::make_pair(WARNING, std::make_pair(std::string("WARN"),  &std::cout)));
    levels.insert(std::make_pair(ERROR,   std::make_pair(std::string("ERROR"), &std::cerr)));
    levels.insert(std::make_pair(FATAL,   std::make_pair(std::string("FATAL"), &std::cerr)));
}

std::string Logger::getCurrentTime() {
    time_t now = time(NULL);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return std::string(buf);
}

void Logger::logMsg(LogPrio level, const std::string& message) {

    if (level < DEBUG || level > FATAL || state == OFF || level < prio) {
        return;
    }

    std::string levelStr = levels[level].first;
    std::ostream* levelStream = levels[level].second;

    std::string logEntry = getCurrentTime() + " [" + levelStr + "] " + message + "\n";
    if (levelStream) {
        (*levelStream) << logEntry;
    }
    
    if (file_.is_open()) {
        file_ << logEntry;
        file_.flush();
    }
}