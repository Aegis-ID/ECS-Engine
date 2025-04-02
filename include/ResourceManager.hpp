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

namespace ECS
{
    class ResourceManager
    {
    private:
        std::unordered_map<std::string, std::shared_ptr<void>> _resources;
    public:
        template<typename T> std::shared_ptr<T> load(const std::string &name, const std::string &filename);
        template<typename T> std::shared_ptr<T> get(const std::string &name);
    };

    template<typename T>
    std::shared_ptr<T> ResourceManager::load(const std::string &name, const std::string &filename)
    {
        if (_resources.find(name) != _resources.end()) {
            auto resource = std::static_pointer_cast<T>(_resources[name]);
            if (resource)
                return resource;
            throw std::runtime_error("Resource exists but has different type");
        }
        auto resource = std::make_shared<T>();
        if (!resource->loadFromFile(filename))
            throw std::runtime_error("Failed to load resource: " + filename);
        _resources[name] = resource;
        return resource;
    }

    template<typename T> std::shared_ptr<T> ResourceManager::get(const std::string &name)
    {
        if (_resources.find(name) == _resources.end())
            return nullptr;
        return std::static_pointer_cast<T>(_resources[name]);
    }
}

/*
 * ResourceManager handles loading and caching game resources like textures, sounds, and fonts.
 * It ensures each resource is loaded only once and provides type-safe access.
 *
 * Key Features:
 * - Efficient resource caching to avoid duplicate loading
 * - Type-safe resource retrieval
 * - Named resource access
 * - Automatic resource cleanup when no longer needed
 *
 * Requirements:
 * - Resource classes must implement a loadFromFile(const std::string& filename) method
 *   that returns bool indicating success or failure
 *
 * Usage example:
 *
 * // Create resource manager
 * ECS::ResourceManager resourceManager;
 *
 * // Load a texture
 * try {
 *     auto texture = resourceManager.load<Texture>("player", "assets/player.png");
 * } catch (const std::runtime_error &e) {
 *     std::cerr << "Error loading resource: " << e.what() << std::endl;
 * }
 *
 * // Get a loaded resource
 * auto texture = resourceManager.get<Texture>("player");
 * if (texture) {
 *     // Use the texture
 * }
 */

#endif /* !__RESOURCEMANAGER_H__ */
