/*
** EPITECH PROJECT, 2025
** DynamicLoader.hpp
** File description:
** DynamicLoader
*/

#ifndef __DynamicLoader__
    #define __DynamicLoader__

    #include <dlfcn.h>
    #include <stdexcept>
    #include <string>
    #include <unordered_map>

namespace Utils 
{
    class DynamicLoader 
    {
    private:
        void *_handle = nullptr;
        std::unordered_map<std::string, void *> _funcLists;

    public:
        DynamicLoader() = default;
        ~DynamicLoader();

        void openFile(const std::string &filePath);
        void closeFile();
        void addSym(const std::string &funcName);

        template<typename T>
        T loadFunc(const std::string &funcName) const;

        std::unordered_map<std::string, void *> getSymList() const;
    };

    template<typename T> T DynamicLoader::loadFunc(const std::string &funcName) const
    {
        auto search = _funcLists.find(funcName);

        if (search != _funcLists.end())
            return reinterpret_cast<T>(search->second);
        throw std::runtime_error("Function not found within the registered functions\n");
    }
}

#endif /* !__DynamicLoader__ */
