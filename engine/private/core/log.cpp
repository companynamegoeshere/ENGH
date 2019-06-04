#include <core/log.hpp>
#include <iostream>

using ENGH::Logger;
using Level = ENGH::Logger::Level;

const Level Level::OFF("OFF", Int32::MAX);
const Level Level::FATAL("FATAL", 1000);
const Level Level::ERROR("ERROR", 900);
const Level Level::WARN("WARN", 800);
const Level Level::INFO("INFO", 700);
const Level Level::DEBUG("DEBUG", 600);
const Level Level::FINE("FINE", 500);
const Level Level::FINER("FINER", 400);
const Level Level::FINEST("FINEST", 300);
const Level Level::ALL("ALL", Int32::MIN);


Logger& ENGH::Logger::getCoreLogger() {
    static Logger logger = Logger(
#ifdef ENGH_DEBUG
            Level::FINE,
#else
            Level::INFO,
#endif
            {std::shared_ptr<std::ostream>(&std::cout, [](std::ostream *) {})},
            {std::shared_ptr<std::ostream>(&std::cerr, [](std::ostream *) {})}
    ).setPrefix("CORE");
    return logger;
}

Logger& ENGH::Logger::getStdLogger() {
    static Logger logger(
#ifdef ENGH_DEBUG
            Level::FINE,
#else
            Level::INFO,
#endif
            {std::shared_ptr<std::ostream>(&std::cout, [](std::ostream *) {})},
            {std::shared_ptr<std::ostream>(&std::cerr, [](std::ostream *) {})}
    );
    return logger;
}

Logger::Logger(Logger::Level level,
               std::initializer_list<std::shared_ptr<std::ostream>> outStreams,
               std::initializer_list<std::shared_ptr<std::ostream>> errStreams
) noexcept : level(level), errorThresholder(Level::INFO) {
    output.insert(output.end(), outStreams.begin(), outStreams.end());
    error.insert(error.end(), errStreams.begin(), errStreams.end());
}

Logger& Logger::setPrefix(std::string_view prefix) {
    this->prefix = std::string("[").append(prefix) + "] ";
    return *this;
}
