/*
** EPITECH PROJECT, 2025
** Logger.cpp
** File description:
** Logger
*/

#include <chrono>
#include <iomanip>
#include <sstream>
#include "Utils/Logger.hpp"

namespace Utils
{
    Logger *Logger::_instance = nullptr;
    std::mutex Logger::_mutex;

    Logger::Logger()
        :   _logLevel(LogLevel::INFO), _consoleOutput(true) {}

    Logger::~Logger()
    {
        closeLogFile();
    }

    Logger &Logger::getInstance()
    {
        std::lock_guard<std::mutex> lock(_mutex);

        if (!_instance)
            _instance = new Logger();
        return *_instance;
    }

    void Logger::setLogLevel(LogLevel level)
    {
        _logLevel = level;
    }

    void Logger::setConsoleOutput(bool enable)
    {
        _consoleOutput = enable;
    }

    bool Logger::openLogFile(const std::string &filename)
    {
        closeLogFile();
        _logFile.open(filename, std::ios::out | std::ios::app);
        return _logFile.is_open();
    }

    void Logger::closeLogFile()
    {
        if (_logFile.is_open())
            _logFile.close();
    }

    std::string Logger::getTimestamp() const
    {
        auto now = std::chrono::system_clock::now();
        auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::tm now_tm;
        std::stringstream ss;
        ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
        ss << '.' << std::setfill('0') << std::setw(3) << now_ms.count();
        return ss.str();
    }

    std::string Logger::logLevelToString(LogLevel level) const
    {
        switch (level) {
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::INFO:
                return "INFO";
            case LogLevel::WARNING:
                return "WARNING";
            case LogLevel::ERROR:
                return "ERROR";
            case LogLevel::FATAL:
                return "FATAL";
            default:
                return "UNKNOWN";
        }
    }
}
