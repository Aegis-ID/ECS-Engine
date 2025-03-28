/*
** EPITECH PROJECT, 2025
** Audio.hpp
** File description:
** Audio
*/

#ifndef __AUDIO_H__
    #define __AUDIO_H__

    #include <string>
    #include "../ComponentWrapper.hpp"

namespace ECS::Components
{
    class AudioComponent : IComponentWrapper
    {
    private:
        std::string _audioPath;
        short _audioLevel;
    public:
        void setAudioPath(std::string);
        void setAudioLevel(short);
    };
}

#endif /* !__AUDIO_H__ */
