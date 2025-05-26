# ECS documentation

## Table of Contents
1. [What is an ECS?](#what-is-an-ecs)
2. [Code Reference](#componentmanager)
   - [ComponentManager](#componentmanager)
   - [IComponentPool & ComponentPool](#icomponentpool--componentpool)
   - [Entity](#entity)
   - [EntityManager](#entitymanager)
   - [SystemManager](#systemmanager)
   - [ISystem](#isystem)
   - [EventManager](#eventmanager)

## What is an ECS?

The Entity Component System (ECS) is an architectural pattern primarily used in game development that focuses on composition over inheritance for maximum flexibility and performance.

### Entities
Entities are the basic objects in your game or application. Here, an entity is essentially just an ID with a signature that indicates which components it has. Entities have no behavior of their own.

### Signatures
Signatures are bitsets that track which components an entity has. They enable efficient filtering of entities for systems.

### Components
Components are pure data structures that store the attributes of entities. Each component type represents a specific aspect of an entity, such as position, rendering information, or health.

### Systems
Systems contain the logic that operates on entities with specific component combinations. Each system processes entities that match its required component signature.

### Events
Events allow for communication between different parts of the system without creating direct dependencies.

## ComponentManager

The `ComponentManager` is responsible for:
- Registering component types in the system
- Assigning unique IDs to each component type
- Creating and managing component pools for each type
- Tracking which entities own which components
- Providing efficient component access

```cpp
// Usage example:

// Create a component manager
ECS::ComponentManager componentManager;

// Register component types
componentManager.registerComponent<PositionComponent>();
componentManager.registerComponent<HealthComponent>();

// Get component type ID
ECS::ComponentType positionType = componentManager.getComponentType<PositionComponent>();

// Get component pool for direct access
auto positionPool = componentManager.getComponentPool<PositionComponent>();

// Get a component for a specific entity
auto playerPosition = componentManager.getEntityComponent<PositionComponent>(playerID);
```

### `template<typename T> ComponentType registerComponent()`
Registers a component type in the system and assigns it a unique ID.

**Returns:**
- `ComponentType`: The assigned component type ID

**Example:**
```cpp
ECS::ComponentManager componentManager;
ECS::ComponentType positionType = componentManager.registerComponent<PositionComponent>();
```

### `template<typename T> ComponentType getComponentType()`
Gets the unique ID of a previously registered component type.

**Returns:**
- `ComponentType`: The component type ID

**Throws:**
- `std::runtime_error`: If the component type is not registered

**Example:**
```cpp
ECS::ComponentType healthType = componentManager.getComponentType<HealthComponent>();
```

### `template<typename T> std::shared_ptr<ComponentPool<T>> getComponentPool()`
Gets the component pool for a specific component type.

**Returns:**
- `std::shared_ptr<ComponentPool<T>>`: The component pool

**Throws:**
- `std::runtime_error`: If the component type is not registered

**Example:**
```cpp
auto positionPool = componentManager.getComponentPool<PositionComponent>();
```

### `template<typename T> void setComponentOwner(std::shared_ptr<T>, EntityID)`
Associates a component with an entity.

**Parameters:**
- `component`: The component to associate
- `entityID`: The ID of the entity

**Example:**
```cpp
auto position = positionPool->create();
componentManager.setComponentOwner<PositionComponent>(position, entityID);
```

### `template<typename T> std::shared_ptr<T> getEntityComponent(EntityID)`
Gets a component for a specific entity.

**Parameters:**
- `entityID`: The ID of the entity

**Returns:**
- `std::shared_ptr<T>`: The component, or nullptr if not found

**Example:**
```cpp
auto health = componentManager.getEntityComponent<HealthComponent>(playerID);
```

### `template<typename T> void removeEntityComponent(EntityID)`
Removes a component from an entity.

**Parameters:**
- `entityID`: The ID of the entity

**Example:**
```cpp
componentManager.removeEntityComponent<TemporaryEffectComponent>(enemyID);
```

## IComponentPool & ComponentPool

`IComponentPool` defines the interface for component storage, while `ComponentPool<T>` implements efficient storage and retrieval for a specific component type.

```cpp
//Usage example:

// Create a component pool
auto positionPool = std::make_shared<ECS::ComponentPool<PositionComponent>>();

// Create a component
auto position = positionPool->create();
position->x = 100.0f;
position->y = 200.0f;

// Get index for component lookup
size_t index = positionPool->getIndex(position);

// Retrieve component by index
auto samePosition = positionPool->getByIndex(index);

// Get all active components
auto allPositions = positionPool->getAllActive();

// Destroy component when no longer needed
// (Usually handled automatically when shared_ptr reference count reaches zero)
positionPool->destroy(index);
```

### `std::shared_ptr<T> create()`
Creates a new component in the pool.

**Returns:**
- `std::shared_ptr<T>`: The newly created component

**Example:**
```cpp
auto position = positionPool->create();
```

### `void destroy(std::size_t index)`
Destroys a component at the specified index.

**Parameters:**
- `index`: The index of the component to destroy

**Example:**
```cpp
positionPool->destroy(ComponentID);
```

### `std::vector<std::shared_ptr<T>> getAllActive()`
Gets all active components in the pool.

**Returns:**
- `std::vector<std::shared_ptr<T>>`: All active components

**Example:**
```cpp
auto allPositions = positionPool->getAllActive();
```

### `size_t getIndex(const std::shared_ptr<T> &component)`
Gets the index of a component in the pool.

**Parameters:**
- `component`: The component to find

**Returns:**
- `size_t`: The index of the component

**Example:**
```cpp
size_t index = positionPool->getIndex(position);
```

### `std::shared_ptr<T> getByIndex(size_t index)`
Gets a component by its index.

**Parameters:**
- `index`: The index of the component

**Returns:**
- `std::shared_ptr<T>`: The component, or nullptr if not found

**Example:**
```cpp
auto position = positionPool->getByIndex(ComponentID);
```

## Entity

The `Entity` class represents an individual game object that can have multiple components.
Each entity is essentially an ID with a signature that indicates which components it has.

```cpp
//Usage example:

// Create an entity with a component manager
auto entity = std::make_shared<ECS::Entity>(componentManager);
entity->setID(entityID);

// Add components
entity->addComponent<PositionComponent>();
entity->addComponent<RenderComponent>();

// Check for a component
if (entity->hasComponent<CollisionComponent>()) {
    // Handle collision
}

// Get a component
auto position = entity->getComponent<PositionComponent>();
if (position) {
    position->x += 10.0f;
}

// Remove a component
entity->removeComponent<TemporaryEffectComponent>();
```

### `void setID(EntityID id)`
Sets the unique ID of the entity.

**Parameters:**
- `id`: The ID to set

**Example:**
```cpp
entity->setID(nextEntityID++);
```

### `EntityID getID() const`
Gets the unique ID of the entity.

**Returns:**
- `EntityID`: The entity's ID

**Example:**
```cpp
EntityID id = entity->getID();
```

### `Signature getSignature() const`
Gets the component signature of the entity.

**Returns:**
- `Signature`: The entity's component signature

**Example:**
```cpp
Signature signature = entity->getSignature();
```

### `template<typename T> void addComponent()`
Adds a component of type T to the entity.

**Example:**
```cpp
entity->addComponent<PositionComponent>();
```

### `template<typename T> void removeComponent()`
Removes a component of type T from the entity.

**Example:**
```cpp
entity->removeComponent<TemporaryEffectComponent>();
```

### `template<typename T> std::shared_ptr<T> getComponent()`
Gets a component of type T from the entity.

**Returns:**
- `std::shared_ptr<T>`: The component, or nullptr if not found

**Example:**
```cpp
auto position = entity->getComponent<PositionComponent>();
```

### `template<typename T> bool hasComponent() const`
Checks if the entity has a component of type T.

**Returns:**
- `bool`: True if the entity has the component, false otherwise

**Example:**
```cpp
if (entity->hasComponent<CollisionComponent>()) {
    // Handle collision
}
```

## EntityManager

The `EntityManager` is responsible for:
- Creating and destroying entities
- Tracking entity signatures for component-based filtering
- Providing access to entities by ID
- Managing entity component signatures

```cpp
// Usage example:

// Create entity manager with component manager
auto entityManager = std::make_shared<ECS::EntityManager>(componentManager);

// Create a new entity
auto entity = entityManager->createEntity();

// Add components and update signature
entity->addComponent<PositionComponent>();
entityManager->onComponentAdded<PositionComponent>(entity->getID());

// Find entities with specific components
ECS::Signature signature;
signature.set(componentManager->getComponentType<PositionComponent>());
signature.set(componentManager->getComponentType<RenderComponent>());
auto renderableEntities = entityManager->getEntitiesWithSignature(signature);

// Destroy entity when no longer needed
entityManager->destroyEntity(entity->getID());
```

### `EntityManager(std::shared_ptr<ComponentManager> componentManager)`
Constructor that takes a component manager.

**Parameters:**
- `componentManager`: A shared pointer to a component manager

**Example:**
```cpp
auto componentManager = std::make_shared<ECS::ComponentManager>();
auto entityManager = std::make_shared<ECS::EntityManager>(componentManager);
```

### `std::shared_ptr<Entity> createEntity()`
Creates a new entity.

**Returns:**
- `std::shared_ptr<Entity>`: The newly created entity

**Example:**
```cpp
auto player = entityManager->createEntity();
```

### `void destroyEntity(EntityID)`
Destroys an entity with the specified ID.

**Parameters:**
- `entityID`: The ID of the entity to destroy

**Example:**
```cpp
entityManager->destroyEntity(enemyID);
```

### `template<typename T> void onComponentAdded(EntityID entityID)`
Updates the entity signature when a component is added.

**Parameters:**
- `entityID`: The ID of the entity

**Example:**
```cpp
entity->addComponent<PositionComponent>();
entityManager->onComponentAdded<PositionComponent>(entity->getID());
```

### `template<typename T> void onComponentRemoved(EntityID entityID)`
Updates the entity signature when a component is removed.

**Parameters:**
- `entityID`: The ID of the entity

**Example:**
```cpp
entity->removeComponent<TemporaryEffectComponent>();
entityManager->onComponentRemoved<TemporaryEffectComponent>(entity->getID());
```

### `std::vector<std::shared_ptr<Entity>> getEntitiesWithSignature(Signature)`
Gets all entities that match a specific component signature.

**Parameters:**
- `signature`: The component signature to match

**Returns:**
- `std::vector<std::shared_ptr<Entity>>`: All matching entities

**Example:**
```cpp
Signature signature;
signature.set(componentManager->getComponentType<PositionComponent>());
signature.set(componentManager->getComponentType<RenderComponent>());
auto renderableEntities = entityManager->getEntitiesWithSignature(signature);
```

### `std::shared_ptr<Entity> getEntity(EntityID entityID)`
Gets an entity by its ID.

**Parameters:**
- `entityID`: The ID of the entity

**Returns:**
- `std::shared_ptr<Entity>`: The entity, or nullptr if not found

**Example:**
```cpp
auto player = entityManager->getEntity(playerID);
```

### `std::shared_ptr<ComponentManager> getComponentManager() const`
Gets the ComponentManager member of the class.

**Returns:**
- `std::shared_ptr<ComponentManager>` : The member of the class.

**Example**
```cpp
auto componentManager = _scene.getComponentManager();
```

## SystemManager

The `SystemManager` is responsible for creating, tracking, and updating systems.
Systems are responsible for processing entities and implementing game logic.

```cpp
// Usage example:

// Create system manager
ECS::SystemManager systemManager;

// Register systems
auto movementSystem = systemManager.registerSystem<MovementSystem>();
auto collisionSystem = systemManager.registerSystem<CollisionSystem>();

// Configure systems
movementSystem->setEntityManager(entityManager);

// Update all systems
float deltaTime = 0.016f; // ~60 FPS
systemManager.update(deltaTime);

// Get a specific system
auto renderSystem = systemManager.getSystem<RenderSystem>();
if (renderSystem) {
    renderSystem->render();
}
```

### `template<typename T> std::shared_ptr<T> registerSystem()`
Registers a system of type T.

**Returns:**
- `std::shared_ptr<T>`: The newly registered system

**Example:**
```cpp
auto movementSystem = systemManager->registerSystem<MovementSystem>();
```

### `template<typename T> std::shared_ptr<T> getSystem()`
Gets a system of type T.

**Returns:**
- `std::shared_ptr<T>`: The system, or nullptr if not found

**Example:**
```cpp
auto renderSystem = systemManager->getSystem<RenderSystem>();
```

### `void addSystem(std::shared_ptr<ISystem> system)`
Adds a system to the manager.

**Parameters:**
- `system`: The system to add

**Example:**
```cpp
auto customSystem = std::make_shared<CustomSystem>();
systemManager->addSystem(customSystem);
```

### `void update(float deltaTime)`
Updates all systems.

**Parameters:**
- `deltaTime`: The time elapsed since the last update

**Example:**
```cpp
float deltaTime = 0.016f; // ~60 FPS
systemManager->update(deltaTime);
```

## ISystem

The `ISystem` defines the interface for all systems in the ECS architecture.
Systems provide the logic that operates on entities with specific component combinations.

```cpp
//Usage example:

class HealthSystem : public ECS::ISystem
{
private:
    std::vector<std::shared_ptr<Entity>> _entities;
    std::shared_ptr<EntityManager> _entityManager;

public:
    void initialize(std::shared_ptr<EntityManager> entityManager)
    {
        _entityManager = entityManager;
        // Set up signature to filter relevant entities
        ECS::Signature signature;
        signature.set(componentManager->getComponentType<HealthComponent>());
        _entities = _entityManager->getEntitiesWithSignature(signature);
    }

    void update(float deltaTime) override
    {
        processEntities();
    }

    void processEntities() override
    {
        for (auto& entity : _entities) {
            auto health = entity->getComponent<HealthComponent>();

            if (health && health->getCurrentHealth() <= 0) {
                // Handle entity death
            }
        }
    }
};
```

### `virtual void update(float deltaTime) = 0`
Updates the system with the elapsed time.

**Parameters:**
- `deltaTime`: The time elapsed since the last update

**Example:**
```cpp
void MovementSystem::update(float deltaTime) override {
    processEntities();
}
```

### `virtual void processEntities() = 0`
Processes all entities that match the system's requirements.

**Example:**
```cpp
void MovementSystem::processEntities() override {
    for (auto& entity : _entities) {
        auto position = entity->getComponent<PositionComponent>();
        auto velocity = entity->getComponent<VelocityComponent>();

        if (position && velocity) {
            position->x += velocity->x * _deltaTime;
            position->y += velocity->y * _deltaTime;
        }
    }
}
```

## EventManager

The `EventManager` allows components and systems to communicate without direct dependencies.

````cpp
// Usage example:

// Define an event
struct CollisionEvent {
    EntityID entity1;
    EntityID entity2;
};

// Create event manageR
ECS::EventManager eventManager;

// Subscribe to event
eventManager.subscribe<CollisionEvent>([](const CollisionEvent& event) {
    std::cout << "Collision between " << event.entity1 << " and " << event.entity2 << std::endl;
});

// Emit an event
CollisionEvent collision = { player->getID(), enemy->getID() };
eventManager.emit(collision);

// Events are automatically cleaned up after all handlers are called
```

### `template<typename EventType> void subscribe(std::function<void(const EventType &)>)`
Subscribes to events of a specific type.

**Parameters:**
- `handler`: A function to handle the event

**Example:**
```cpp
eventManager->subscribe<CollisionEvent>([](const CollisionEvent& event) {
    std::cout << "Collision between " << event.entity1 << " and " << event.entity2 << std::endl;
});
```

### `template<typename EventType> void emit(const EventType &)`
Emits an event of a specific type.

**Parameters:**
- `event`: The event to emit

**Example:**
```cpp
CollisionEvent collision = { player->getID(), enemy->getID() };
eventManager->emit(collision);
```
