/*
** EPITECH PROJECT, 2025
** Core.cpp
** File description:
** Core
*/

#include <libconfig.h++>
#include "Engine/Core.hpp"

namespace Engine
{
    Core::Core()
    {
        loadLoggerSettings();
        _converter.loadConverter(_sceneManager);
        // init the renderer
        // init the editor
    }
    
    Core::~Core()
    {
        shutdown();
    }

    void Core::run(const std::vector<std::string> &args)
    {
        auto &logger = Utils::Logger::getInstance();

        logger.debug("Core: Initializing Core");
        try {
            if (args.size() > 0)
                loadScenePresets(args);
            _converter.convertScenes();
        } catch (const std::exception &e) {
            logger.fatal("%s", e.what());
        }
    }

    void Core::shutdown()
    {
        auto &logger = Utils::Logger::getInstance();
        
        logger.debug("Core: Core Shutdown");
        logger.destroyInstance();
    }

    LogSettings Core::parseLoggerSettings()
    {
        LogSettings logSetting;
        libconfig::Config cfg;
        const std::unordered_map<std::string, Utils::LogLevel> logMap = 
        {
            {"debug", Utils::LogLevel::DEBUG},
            {"info", Utils::LogLevel::INFO},
            {"warning", Utils::LogLevel::WARNING},
            {"error", Utils::LogLevel::ERROR},
            {"fatal", Utils::LogLevel::FATAL}
        };

        try {
            cfg.readFile(ENGINE_CFG);
            const libconfig::Setting &logSettings = cfg.lookup("LogSettings");
            std::string logLevelStr = logSettings["loglevel"];
            auto it = logMap.find(logLevelStr);
            if (it != logMap.end())
                logSetting._logLevel = it->second;
            logSettings.lookupValue("consoleOutput", logSetting._consoleOutput);
            logSetting._logfile = logSettings["logfile"].c_str();
        } catch (const libconfig::SettingNotFoundException &e) {
            std::cerr << std::string(ENGINE_CFG) + ": Setting not found: "
                + e.getPath() << std::endl;
        } catch (const libconfig::ParseException &e) {
            std::cerr << std::string(ENGINE_CFG) + ": Parse error at line "
                + std::to_string(e.getLine()) + ": " + e.getError() << std::endl;
        }
        return logSetting;
    }

    void Core::loadLoggerSettings()
    {
        auto &logger = Utils::Logger::getInstance();

        _infos.logSettings = parseLoggerSettings();
        logger.setLogLevel(_infos.logSettings._logLevel);
        logger.setConsoleOutput(_infos.logSettings._consoleOutput);
        logger.openLogFile(_infos.logSettings._logfile);
        logger.debug("Logger initialized");
    }

    void Core::loadSettings()
    {
        loadLoggerSettings();
    }

    void Core::loadScenePresets(const std::vector<std::string> &args)
    {
        auto &logger = Utils::Logger::getInstance();

        logger.debug("Core: Load scene preset(s) given as arguments");
        try {
            for (const auto &filepath : args)
                _sceneManager.loadScene(filepath);
        } catch (const std::exception &e) {
            logger.error("Core: %s", e.what());
        }
    }
}
