# Engine Documentation

This is an Engine Documentation. 

## Table of Contents

1. [Scene](#scenes
2. [Engine Systems](#engine-systems)
- [How to add Core Components](#how-to-add-core-components)
- [How to add new EntityType](#how-to-add-new-plugin-type)
- [Resource Manager](#resource-manager)

## Scene

Scene is a high-level container that brings together all parts of the ECS. It manages entities, components, and systems, and can provides factory methods for creating common entity types.

The engine has the feature to load Scenes Presets. Here is how to make a Scene Preset:

```
scene = "example";          # name of the scene

camera:                         # Mandatory Entity Type
{
    main = (                    # Entity name
    {
        res_width = 1280;
        res_height = 720;
        pos_x = 0;
        pos_y = -100;
        pos_z = 20;
        rot_x = 0;
        rot_y = 0;
        rot_z = 0;
        fov = 72.5;
    });
};

primitive:                  # Entity type
{
    sphere = (              # Entity name
    {
        x = 0;              # the following will be parsed into a EntityConfig type :
        y = 0;              # std::unordered_map<std::string, std::any> EntityConfig
        z = 0;              # the parsing is handled by the plugin so the Engine
        r = 255;            # doesn't need to know the components headers
        g = 255;
        b = 255;
    },
    {                       # can handle multiple config of the same Entity
        x = 50;
        y = 50;
        z = 50;
        r = 254;
        g = 254;
        b = 254;
    });
}
```

## Engine Systems

### How to add Core Components

Note: This is a guide to add Core Components to the Engine, not an ECS usage guide, for more infos about the ECS you can check the ECS.md

You know the title, you know why you are here. So let's just start :
1. You'll have to add in the `include/Engine/Components/` folder the header containing your new Core Component(s). Your component have to be in a namepsace `Engine::CoreComponents`.
2. You'll have to add your component header to the `include/Engine/CoreComponents.hpp`.
3. You'll have to register this CoreComponent through `defaultCM->registerComponent<youComponentType>()` in Scene.cpp `createDefaultComponentManager()`.

### How to add new EntityType

First if you want to add a new EntityType **check that it doesn't already exists**. If not, I invite you to follow the next steps.

You'll have to add in `include/Engine/EntityType.hpp` two things:
1. The enum name of your EntityType in `enum EntityType`
2. The string name of your EntityType in `static constexpr std::string_view EntityTypeNames[]`

Next you'll have to:
1. add to ETCCIndex your EntityType you added it in `enum EntityType`, oh and don't worry about the place, its an unordered map ;).
2. indicate the CoreComponents (if necessary) of your EntityType in Scene.cpp `setEntityTypeCoreComponents`.

### Resource Manager

** IT IS EXPERIMENTAL **

ResourceManager handles loading, caching, and lifecycle management for game resources like textures, sounds, and fonts.
It provides resources to various systems but doesn't process entities itself.

```cpp
// Usage example:

// Example texture resource implementation
class Texture : public Engine::IResource 
{
    [...]
};

// Access the resource manager
auto &resourceManager = Engine::ResourceManager::getInstance();

// Load a texture
auto texture = resourceManager.load<Texture>("player", "assets/player.png");

// In a rendering system:
class RenderSystem : public ECS::ISystem 
{
public:
    void update(float deltaTime) override 
    {
        auto &resourceManager = Engine::ResourceManager::getInstance();
        auto texture = resourceManager.get<Texture>("player");
        
        // Use texture for rendering entities
    }
};
```
