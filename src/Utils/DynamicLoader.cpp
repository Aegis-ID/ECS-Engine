/*
** EPITECH PROJECT, 2025
** DynamicLoader.cpp
** File description:
** DynamicLoader
*/

#include "Utils/DynamicLoader.hpp"
#include <dlfcn.h>
#include <stdexcept>

namespace Utils
{
    DynamicLoader::~DynamicLoader()
    {
        closeFile();
    }

    void DynamicLoader::openFile(const std::string &filePath)
    {
        if (_handle)
            closeFile();
        _handle = dlopen(filePath.c_str(), RTLD_LAZY | RTLD_LOCAL);
        if (!_handle)
            throw std::runtime_error(dlerror());
        _funcLists.clear();
    }

    void DynamicLoader::closeFile()
    {
        if (_handle != nullptr)
            dlclose(_handle);
    }

    void DynamicLoader::addSym(const std::string &funcName)
    {
        if (!_handle)
            throw std::runtime_error("Cannot add symbol: file is not open");

        void *function = dlsym(_handle, funcName.c_str());
        if (!function)
            throw std::runtime_error(dlerror());

        _funcLists[funcName] = function;
    }

    std::unordered_map<std::string, void *> DynamicLoader::getSymList() const
    {
        return _funcLists;
    }
}