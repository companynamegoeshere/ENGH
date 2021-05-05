#pragma once

#include <vector>
#include <ostream>
#include <core/data_types.hpp>
#include <core/debug.hpp>

namespace ENGH {

class Logger {
public:

    class Level {
    public:
        static const Level OFF;
        static const Level FATAL;
        static const Level ERR;
        static const Level WARN;
        static const Level INFO;
        static const Level DEBUG;
        static const Level FINE;
        static const Level FINER;
        static const Level FINEST;
        static const Level ALL;
    private:
        std::string_view m_name;
        int32 m_level;

        constexpr Level(std::string_view name, int32 level) noexcept: m_name(name), m_level(level) {}

    public:
        inline std::string_view &name() { return m_name; }

        inline bool operator>(const Level &other) const { return m_level > other.m_level; }
    };

private:
    Level level;
    Level errorThresholder;

    std::string prefix;

    std::vector<std::shared_ptr<std::ostream>> output;
    std::vector<std::shared_ptr<std::ostream>> error;
public:

    static Logger &getCoreLogger();

    static Logger &getStdLogger();

    explicit Logger(Level level,
                    std::initializer_list<std::shared_ptr<std::ostream>> outStreams = {},
                    std::initializer_list<std::shared_ptr<std::ostream>> errStreams = {}
    ) noexcept;

    template<typename...Ts>
    inline void log(Level level, Ts... ts) const {
        if (this->level > level) {
            return;
        }
        for (const auto &stream : level > errorThresholder ? error : output) {
          if (prefix.length()) {
            *stream << prefix;
          }
          *stream << "<" << level.name() << "> ";
          (*stream << ... << ts) << std::endl;
        }
    }

  Logger &setPrefix(std::string_view prefix);

  void SetLevel(Level level);

};

namespace Util::String {
template<typename...Ts>
static std::string concat(std::string first, Ts... ts) {
    return (first + ... + ts);
}
}

}

#define ENGH_CORE_THROW_FATAL(...) do { ENGH_CORE_FATAL(__VA_ARGS__); ENGH::Debug::Break(); } while(0)
#define ENGH_CORE_FATAL(...) ::ENGH::Logger::getCoreLogger().log(::ENGH::Logger::Level::FATAL, __VA_ARGS__)
#define ENGH_CORE_ERROR(...) ::ENGH::Logger::getCoreLogger().log(::ENGH::Logger::Level::ERR, __VA_ARGS__)
#define ENGH_CORE_WARN(...) ::ENGH::Logger::getCoreLogger().log(::ENGH::Logger::Level::WARN, __VA_ARGS__)
#define ENGH_CORE_INFO(...) ::ENGH::Logger::getCoreLogger().log(::ENGH::Logger::Level::INFO, __VA_ARGS__)
#define ENGH_CORE_LOG_DEBUG(...) ::ENGH::Logger::getCoreLogger().log(::ENGH::Logger::Level::DEBUG, __VA_ARGS__)
#define ENGH_CORE_FINE(...) ::ENGH::Logger::getCoreLogger().log(::ENGH::Logger::Level::FINE, __VA_ARGS__)
#define ENGH_CORE_FINER(...) ::ENGH::Logger::getCoreLogger().log(::ENGH::Logger::Level::FINER, __VA_ARGS__)
#define ENGH_CORE_FINEST(...) ::ENGH::Logger::getCoreLogger().log(::ENGH::Logger::Level::FINEST, __VA_ARGS__)

#define ENGH_THROW_FATAL(...) do { ENGH_FATAL(__VA_ARGS__); ENGH::Debug::Break(); } while(0)
#define ENGH_FATAL(...) ::ENGH::Logger::getStdLogger().log(::ENGH::Logger::Level::FATAL, __VA_ARGS__)
#define ENGH_ERROR(...) ::ENGH::Logger::getStdLogger().log(::ENGH::Logger::Level::ERR, __VA_ARGS__)
#define ENGH_WARN(...) ::ENGH::Logger::getStdLogger().log(::ENGH::Logger::Level::WARN, __VA_ARGS__)
#define ENGH_INFO(...) ::ENGH::Logger::getStdLogger().log(::ENGH::Logger::Level::INFO, __VA_ARGS__)
#define ENGH_LOG_DEBUG(...) ::ENGH::Logger::getStdLogger().log(::ENGH::Logger::Level::DEBUG, __VA_ARGS__)
#define ENGH_FINE(...) ::ENGH::Logger::getStdLogger().log(::ENGH::Logger::Level::FINE, __VA_ARGS__)
#define ENGH_FINER(...) ::ENGH::Logger::getStdLogger().log(::ENGH::Logger::Level::FINER, __VA_ARGS__)
#define ENGH_FINEST(...) ::ENGH::Logger::getStdLogger().log(::ENGH::Logger::Level::FINEST, __VA_ARGS__)

