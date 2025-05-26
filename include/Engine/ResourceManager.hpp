/*
** EPITECH PROJECT, 2025
** ResourceManager.hpp
** File description:
** ResourceManager
*/

#ifndef __RESOURCEMANAGER_H__
    #define __RESOURCEMANAGER_H__

    #include <memory>
    #include <stdexcept>
    #include <unordered_map>
    #include <string>
    #include <typeindex>

namespace Engine
{
    class IResource
    {
    public:
        virtual ~IResource() = default;
        virtual bool loadFromFile(const std::string &filename) = 0;
        virtual void unload() = 0;
        virtual bool isLoaded() const = 0;
    };

    class ResourceManager
    {
    private:
        std::unordered_map<std::type_index, std::unordered_map<std::string, std::shared_ptr<IResource>>> _resources;
        std::unordered_map<std::type_index, std::unordered_map<std::string, std::string>> _filenames;
    public:
        static ResourceManager &getInstance() 
        {
            static ResourceManager instance;
            return instance;
        }
        template<typename T>
            std::shared_ptr<T> load(const std::string &name, const std::string &filename);
        template<typename T>
            std::shared_ptr<T> get(const std::string &name);
        template<typename T>
            std::unordered_map<std::string, std::shared_ptr<T>> getAllOfType();
        template<typename T>
            bool exists(const std::string &name) const;
        template<typename T>
            void unload(const std::string &name);
        template<typename T>
            void unloadAll();
        void unloadAll();
        template<typename T>
            bool reload(const std::string &name);
    };

    template<typename T>
    std::shared_ptr<T> ResourceManager::load(const std::string &name, const std::string &filename)
    {
        const std::type_index typeIndex = std::type_index(typeid(T));
        std::shared_ptr<T> resource;

        if (_resources.find(typeIndex) != _resources.end() && 
            _resources[typeIndex].find(name) != _resources[typeIndex].end())
            return std::static_pointer_cast<T>(_resources[typeIndex][name]);
        resource = std::make_shared<T>();
        if (!resource->loadFromFile(filename))
            throw std::runtime_error("Failed to load resource: " + filename);
        _resources[typeIndex][name] = resource;
        _filenames[typeIndex][name] = filename;
        return resource;
    }

    template<typename T>
    std::shared_ptr<T> ResourceManager::get(const std::string &name)
    {
        const std::type_index typeIndex = std::type_index(typeid(T));
        
        if (_resources.find(typeIndex) == _resources.end() ||
            _resources[typeIndex].find(name) == _resources[typeIndex].end())
            return nullptr;
        return std::static_pointer_cast<T>(_resources[typeIndex][name]);
    }

    template<typename T>
    std::unordered_map<std::string, std::shared_ptr<T>> ResourceManager::getAllOfType()
    {
        std::unordered_map<std::string, std::shared_ptr<T>> result;
        const std::type_index typeIndex = std::type_index(typeid(T));
        
        if (_resources.find(typeIndex) == _resources.end())
            return result;
        for (auto &[name, resource] : _resources[typeIndex])
            result[name] = std::static_pointer_cast<T>(resource);
        return result;
    }

    template<typename T>
    bool ResourceManager::exists(const std::string &name) const
    {
        const std::type_index typeIndex = std::type_index(typeid(T));
        
        return _resources.find(typeIndex) != _resources.end() &&
            _resources.at(typeIndex).find(name) != _resources.at(typeIndex).end();
    }

    template<typename T>
    void ResourceManager::unload(const std::string &name)
    {
        const std::type_index typeIndex = std::type_index(typeid(T));

        if (_resources.find(typeIndex) == _resources.end() ||
            _resources[typeIndex].find(name) == _resources[typeIndex].end())
            return;
        _resources[typeIndex][name]->unload();
        _resources[typeIndex].erase(name);
        _filenames[typeIndex].erase(name);
    }

    template<typename T>
    void ResourceManager::unloadAll()
    {
        const std::type_index typeIndex = std::type_index(typeid(T));
        
        if (_resources.find(typeIndex) == _resources.end())
            return;
        for (auto &[name, resource] : _resources[typeIndex])
            resource->unload();
        _resources[typeIndex].clear();
        _filenames[typeIndex].clear();
    }

    inline void ResourceManager::unloadAll()
    {
        for (auto &[type, resourceMap] : _resources)
            for (auto &[name, resource] : resourceMap)
                resource->unload();
        _resources.clear();
        _filenames.clear();
    }

    template<typename T>
    bool ResourceManager::reload(const std::string &name)
    {
        const std::type_index typeIndex = std::type_index(typeid(T));
        
        if (_filenames.find(typeIndex) == _filenames.end() ||
            _filenames[typeIndex].find(name) == _filenames[typeIndex].end())
            return false;

        const std::string &filename = _filenames[typeIndex][name];
        auto resource = std::static_pointer_cast<T>(_resources[typeIndex][name]);

        resource->unload();
        return resource->loadFromFile(filename);
    }
}


#endif /* !__RESOURCEMANAGER_H__ */
