/*
** EPITECH PROJECT, 2025
** Core.hpp
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include "Utils/Logger.hpp"
    #include "Engine/SceneManager.hpp"
    #include "Engine/Systems/RTConverter.hpp"

namespace Engine
{
    #define ENGINE_CFG "engine.cfg"

    struct LogSettings
    {
        Utils::LogLevel _logLevel = Utils::LogLevel::DEBUG;
        bool _consoleOutput = false;
        std::string _logfile = "engine.log";
    };

    struct EngineInfos
    {
        LogSettings logSettings;
    };

    class Core
    {
    private:
        EngineInfos _infos;
        SceneManager _sceneManager;
        RTConverter _converter;
        bool _loop;

        LogSettings parseLoggerSettings();
        void loadLoggerSettings();

        void loadSettings();
        void loadScenePresets(const std::vector<std::string> &);
    public:
        Core();
        ~Core();

        void run(const std::vector<std::string> &args);
        void shutdown();
    };
}

#endif /* !CORE_HPP_ */
