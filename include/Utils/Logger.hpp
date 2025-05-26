/*
** EPITECH PROJECT, 2025
** Logger.hpp
** File description:
** Logger
*/

#ifndef __LOGGER_H__
    #define __LOGGER_H__

    #include <iostream>
    #include <memory>
    #include <vector>
    #include <string>
    #include <fstream>
    #include <mutex>
    #include <cstdio>

namespace Utils
{
    enum class LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    class Logger
    {
    private:
        static Logger *_instance;
        static std::mutex _mutex;

        LogLevel _logLevel;
        bool _consoleOutput;
        std::ofstream _logFile;

        std::string getTimestamp() const;
        std::string logLevelToString(LogLevel level) const;

    protected:
        Logger();
        ~Logger();
    public:
        static Logger &getInstance();
        void destroyInstance();

        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;

        void setLogLevel(LogLevel level);
        void setConsoleOutput(bool enable);
        bool openLogFile(const std::string& filename);
        void closeLogFile();

        template<typename... Args>
        void log(LogLevel level, const std::string &format, Args... args);

        template<typename... Args>
        void debug(const std::string &format, Args... args);

        template<typename... Args>
        void info(const std::string &format, Args... args);

        template<typename... Args>
        void warning(const std::string &format, Args... args);

        template<typename... Args>
        void error(const std::string &format, Args... args);

        template<typename... Args>
        void fatal(const std::string &format, Args... args);
    };

    template<typename... Args>
    void Logger::log(LogLevel level, const std::string &message, Args... args)
    {
        if (level < _logLevel)
            return;

        std::lock_guard<std::mutex> lock(_mutex);
        std::string timestamp = getTimestamp();
        std::string levelStr = logLevelToString(level);

        #ifdef __GNUC__                 // -> source of this (pas tant que ça en vrai) Dark Magic : 
        #pragma GCC diagnostic push     // https://stackoverflow.com/questions/3378560/how-to-disable-gcc-warnings-for-a-few-lines-of-code
        #pragma GCC diagnostic ignored "-Wformat-security"  // Fuck you ubuntu, 3 fucking days of torments bc of u
        #endif

        int size = std::snprintf(nullptr, 0, message.c_str(), args...) + 1;

        if (size <= 0)
            return;

        std::vector<char> buf(size);
        std::snprintf(buf.data(), size, message.c_str(), args...);
        std::string formattedMessage(buf.data(), buf.data() + size - 1);
        std::string logMessage = timestamp + " [" + levelStr + "] " + formattedMessage;

        #ifdef __GNUC__
        #pragma GCC diagnostic pop
        #endif

        if (_consoleOutput)
            std::cout << logMessage << std::endl;
        if (_logFile.is_open()) {
            _logFile << logMessage << std::endl;
            _logFile.flush();
        }
    }

    template<typename... Args>
    void Logger::debug(const std::string &format, Args... args)
    {
        log(LogLevel::DEBUG, format, args...);
    }

    template<typename... Args>
    void Logger::info(const std::string &format, Args... args)
    {
        log(LogLevel::INFO, format, args...);
    }

    template<typename... Args>
    void Logger::warning(const std::string &format, Args... args)
    {
        log(LogLevel::WARNING, format, args...);
    }

    template<typename... Args>
    void Logger::error(const std::string &format, Args... args)
    {
        log(LogLevel::ERROR, format, args...);
    }

    template<typename... Args>
    void Logger::fatal(const std::string &format, Args... args)
    {
        log(LogLevel::FATAL, format, args...);
    }
}

/*
 * Usage example:
 *
 * // Get logger instance
 * auto &logger = Utils::Logger::getInstance();
 * 
 * // Configure logger
 * logger.setLogLevel(Utils::LogLevel::DEBUG);
 * logger.setConsoleOutput(true);
 * logger.openLogFile("ecs_engine.log");
 * 
 * // Log messages
 * logger.debug("Initializing component %s", "PositionComponent");
 * logger.info("Created entity with ID: %d", entity->getID());
 * logger.warning("Low memory: %d KB available", availableMemory);
 * logger.error("Failed to load resource: %s", filename);
 * logger.fatal("Unrecoverable error: %s", errorMessage);
 *
 * // Log levels: DEBUG < INFO < WARNING < ERROR < FATAL
 * // Messages below the set log level will be ignored
 */

#endif /* !__LOGGER_H__ */

