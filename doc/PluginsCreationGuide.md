# Plugin Creation Guide

This guide explains how to create, implement, and use plugins in the huh... Aegis-Engine v4. (gotta find a better name one day)
Plugins provide a way to extend the engine's functionality by adding new components, systems, and entity types without modifying the core engine code.
The only cost was my sanity...

Note: This is a plugin creation guide, not an ECS usage guide, for more infos about the ECS you can check the ECS.md

## Table of Contents

1. [Plugin Architecture Overview](#plugin-architecture-overview)
2. [Creating a New Plugin](#creating-a-new-plugin)
3. [Implementing Plugin Methods](#implementing-plugin-methods)
4. [Component Implementation](#component-implementation)
5. [System Implementation](#system-implementation)
6. [Entity Factory Methods](#entity-factory-methods)
7. [Building Plugins](#building-plugins)
8. [Debugging Plugins](#debugging-plugins)

## Plugin Architecture Overview

The plugin system in this Engine uses dynamic loading to extend the engine at runtime. Each plugin:

- Is compiled as a shared library (.so)
- Implements the `IPlugin` interface
- Registers components, systems, and entity factory methods
- Can be loaded and unloaded dynamically

The relationship between plugins and the core engine:

```
+------------------+      +----------------------+
|     Engine       |      |       Plugin         |
|                  |      |                      |
|  Scene           |<---->|  Components          |
|  EntityManager   |      |  Systems             |
|  SystemManager   |      |  Factory Methods     |
|  ComponentManager|      |                      |
|  EventManager    |      |                      |
+------------------+      +----------------------+
```

## Creating a New Plugin

### Rules

1. **Keep Plugins Focused**: Each plugin should have a specific purpose
2. **Dependencies**: Clearly document any dependencies between plugins
3. **Assets**: If your plugin uses assets (until we create our own plugin type such as WAD -> see in DOOM), your assets will have to be in the assets/nameOfYourPlugin/

### 1. Create Plugin Class

Start by creating a class that implements the `IPlugin` interface:

```cpp
#include "IPlugin.hpp"
#include "Scene.hpp"

class MyPlugin : public Engine::IPlugin
{
private:
    // Plugin-specific data
public:
    // Required interface implementations
    std::string getName() const override;
    std::string getAuthor() const override;
    std::string getDescription() const override;
    Engine::Version getVersion() const override;
    Engine::EntityType getType() const override;

    bool initialize(Engine::Scene &scene) override;
    bool shutdown() override;

    void registerFactory(Engine::Scene &scene) override;
    void registerSystems(Engine::Scene &scene) override;
    void configureSystems(Engine::Scene &scene) override;
};

// Export plugin creation function
EXPORT_PLUGIN(MyPlugin)
```

### 2. Implement Basic Methods

Implement the basic identification methods:

```cpp
std::string MyPlugin::getName() const
{
    return "BlueMoonSugar";
}

std::string MyPlugin::getAuthor() const
{
    return "Heisenberg";
}

std::string MyPlugin::getDescription() const
{
    return "SayMyName";
}

Engine::Version MyPlugin::getVersion() const
{
    return {1, 0, 0}; // Major, Minor, Patch
}

Engine::EntityType MyPlugin::getType() const
{
    return Engine::EntityType::TRANSFORMATION; // Choose between the proposed types
}
```

## Implementing Plugin Methods

### Initialize and Shutdown

The `initialize` method is called when the plugin is loaded, and `shutdown` when it's unloaded:

```cpp
bool MyPlugin::initialize(Engine::Scene &scene)
{
    // Register components with the component manager
    auto componentManager = scene.getComponentManager();

    componentManager->registerComponent<MyPositionComponent>();
    componentManager->registerComponent<MyVelocityComponent>();
    // Any other initialization logic
    return true; // Return false if initialization fails
}

bool MyPlugin::shutdown()
{
    // Clean up resources
    return true; // Return false if shutdown fails
}
```
### EntityConfig

EntityConfig is a `std::unordered_map<std::string, std::any>` containing:

- a variable name
- a value  

It is used by the plugin/entity factory method to set the components data without the Engine having these components (*insert* "Absolute Cinema").  
The variable name must be the same as the one used in the plugin.

Notes: We can always change the data type for config, if this one isn't satisyfing but it'll do the job for now.


### Register Factory Methods

Factory methods create preconfigured entities:

```cpp
void MyPlugin::registerFactory(Engine::Scene &scene)
{
    // Register factory method for creating entities
    scene.registerEntityFactory(
        getType(), 
        "MovingObject",
        [&scene](const std::string &name, const Engine::EntityConfig &config)
        {
            // Create entity with required components
            auto entity = scene.getEntityManager()->createEntity();

            // Add components
            entity->addComponent<MyPositionComponent>();
            entity->addComponent<MyVelocityComponent>();
            
            // Configure components using config parameters
            auto position = entity->getComponent<MyPositionComponent>();
            auto velocity = entity->getComponent<MyVelocityComponent>();

            // Set values from config
            // the initial values in case config fails
            float x = 0.0f, y = 0.0f;
            if (config.find("x") != config.end())
                x = config.at("x");
            if (config.find("y") != config.end())
                y = config.at("y");

            position->x = x;
            position->y = y;

            // Update entity signature
            scene.getEntityManager()->onComponentAdded<MyPositionComponent>(entity->getID());
            scene.getEntityManager()->onComponentAdded<MyVelocityComponent>(entity->getID());

            return entity;
        }
    );
}
```

### Register Systems

The `registerSystems` method creates and registers plugin-specific systems:

```cpp
void MyPlugin::registerSystems(Engine::Scene &scene)
{
    // Register systems with the system manager
    auto systemManager = scene.getSystemManager();

    systemManager->registerSystem<MyMovementSystem>();
}
```

### Configure Systems

The `configureSystems` method sets up systems after all plugins have registered their systems:

```cpp
void MyPlugin::configureSystems(Engine::Scene &scene)
{
    // Get the system
    auto systemManager = scene.getSystemManager();
    auto movementSystem = systemManager->getSystem<MyMovementSystem>();

    // Configure the system
    if (movementSystem) {
        // Set entity manager
        movementSystem->setEntityManager(scene.getEntityManager());

        // Set component requirements
        // This will be used to filter entities
        movementSystem->setComponentRequirements<MyPositionComponent, MyVelocityComponent>();
    }
}
```

## Component Implementation

Define plugin-specific components:

(Components can be struct or class for more infos about the ECS go check the ECS.md)

```cpp
// MyComponents.hpp
#ifndef MY_COMPONENTS_HPP
    #define MY_COMPONENTS_HPP

struct MyPositionComponent {
    float x = 0.0f;
    float y = 0.0f;
};

struct MyVelocityComponent {
    float vx = 0.0f;
    float vy = 0.0f;
};

#endif
```

## System Implementation

Implement systems that operate on your components:

```cpp
// MyMovementSystem.hpp
#ifndef MY_MOVEMENT_SYSTEM_HPP
#define MY_MOVEMENT_SYSTEM_HPP

#include "ECS/ISystem.hpp"
#include "ECS/EntityManager.hpp"
#include "MyComponents.hpp"
#include <memory>
#include <vector>

class MyMovementSystem : public ECS::ISystem
{
private:
    std::shared_ptr<ECS::EntityManager> _entityManager;
    ECS::Signature _EntityTypeCoreComponents;
    std::vector<std::shared_ptr<ECS::Entity>> _matchingEntities;
    
public:
    void setEntityManager(std::shared_ptr<ECS::EntityManager> entityManager)
    {
        _entityManager = entityManager;
    }
    
    template<typename... Components>
    void setComponentRequirements()
    {
        if (!_entityManager)
            return;

        auto componentManager = _entityManager->getComponentManager();
        if (!componentManager)
            return;

        // Build signature
        ECS::Signature signature;

        signature.set(componentManager->getComponentType<Components1>());
        signature.set(componentManager->getComponentType<Components2>());
        signature.set(componentManager->getComponentType<ComponentsNth>());

        _EntityTypeCoreComponents = signature;

        // Find matching entities
        if (_entityManager)
            _matchingEntities = _entityManager->getEntitiesWithSignature(_EntityTypeCoreComponents);
    }

    void update(float deltaTime) override 
    {
        // Find matching entities
        if (_entityManager)
            _matchingEntities = _entityManager->getEntitiesWithSignature(_EntityTypeCoreComponents);

        // Process entities
        processEntities();
    }
    
    void processEntities() override
    {
        for (auto& entity : _matchingEntities) {
            auto position = entity->getComponent<MyPositionComponent>();
            auto velocity = entity->getComponent<MyVelocityComponent>();

            if (position && velocity) {
                position->x += velocity->vx;
                position->y += velocity->vy;
            }
        }
    }
};

#endif
```

This is an example... don't do everything in the header. You'll have to compile it as .so anyway...

## Entity Factory Methods

Factory methods provide a convenient way to create common entity types:

```cpp
// Register multiple factory methods for different entity types
void MyPlugin::registerFactory(Engine::Scene &scene)
{
    // Basic moving object
    scene.registerEntityFactory(
        getType(), 
        "MovingObject",
        [&scene](const std::string &name, const Engine::EntityConfig &config)->std::shared_ptr<ECS::Entity>
        {
            // Implementation as shown earlier
            // ...
        }
    );

    // Another type of entity
    scene.registerEntityFactory(
        getType(), 
        "Player",
        [&scene](const std::string &name, const Engine::EntityConfig &config)->std::shared_ptr<ECS::Entity>
        {
            auto entity = scene.getEntityManager()->createEntity();

            // Add components specific to a player
            entity->addComponent<MyPositionComponent>();
            entity->addComponent<MyVelocityComponent>();
            entity->addComponent<MyHealthComponent>();

            // Configure from params
            // ...

            // Update entity signature
            scene.getEntityManager()->onComponentAdded<MyPositionComponent>(entity->getID());
            scene.getEntityManager()->onComponentAdded<MyVelocityComponent>(entity->getID());
            scene.getEntityManager()->onComponentAdded<MyHealthComponent>(entity->getID());

            return entity;
        }
    );
}
```

## Building Plugins

Imagine your plugin as a mini project, which result is a shared library

You can be barbaric and compile your whole project in one line like this:
```bash
# Using g++
g++ -shared -fPIC MyPlugin.cpp MyOtherFiles.cpp -o MyPlugin.so
```
Or be civilised and compile your project with a cmake
```bash
# Using CMake (in CMakeLists.txt)
add_library(MyPlugin SHARED
    MyPlugin.cpp
    MyOtherFiles.cpp
)
```

## Debug

For debugging plugins:

1. **Logging**: Use the **magnificent** Logger Utils
    ```cpp
    Utils::Logger::getInstance().debug("MyPlugin: Entity created with position (%f, %f)", x, y);
    ```

2. **Error Handling**: Add proper error handling in your plugin methods
    ```cpp
    if (!componentManager) {
        std::string error_msg = "MyPlugin: Component manager is null";
        Utils::Logger::getInstance().error(error_msg);
        throw std::exception(error_msg);    // throw are handled
    }
    ```
