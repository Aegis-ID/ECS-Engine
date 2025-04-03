@startuml "ECS Framework Architecture"

' Style settings
skinparam packageStyle rectangle
skinparam classAttributeIconSize 0
skinparam linetype ortho
skinparam shadowing false

package "ECS Framework" {
  ' Core interfaces
  interface IComponentPool {
    + ~IComponentPool(): void
  }

  interface ISystem {
    + ~ISystem(): void
    + update(deltaTime: float): void
    + processEntities(): void
  }

  ' Component management
  class ComponentManager {
    - _nextType: ComponentType
    - _typeMap: unordered_map<type_index, ComponentType>
    - _componentPools: unordered_map<ComponentType, shared_ptr<IComponentPool>>
    - _entityComponentMap: unordered_map<ComponentType, unordered_map<EntityID, size_t>>
    + registerComponent<T>(): ComponentType
    + getComponentType<T>(): ComponentType
    + getComponentPool<T>(): shared_ptr<ComponentPool<T>>
    + setComponentOwner<T>(component: shared_ptr<T>, entityID: EntityID): void
    + getEntityComponent<T>(entityID: EntityID): shared_ptr<T>
    + removeEntityComponent<T>(entityID: EntityID): void
  }

  class "ComponentPool<T>" {
    - _components: vector<shared_ptr<T>>
    - _activeComponents: vector<bool>
    - _freeIndices: queue<size_t>
    + create(): shared_ptr<T>
    + destroy(index: size_t): void
    + getAllActive(): vector<shared_ptr<T>>
    + getIndex(component: shared_ptr<T>): size_t
    + getByIndex(index: size_t): shared_ptr<T>
  }

  ' Entity management
  class Entity {
    - _id: EntityID
    - _signature: Signature
    - _componentManager: shared_ptr<ComponentManager>
    + setID(id: EntityID): void
    + getID(): EntityID
    + getSignature(): Signature
    + addComponent<T>(): void
    + removeComponent<T>(): void
    + getComponent<T>(): shared_ptr<T>
    + hasComponent<T>(): bool
  }

  class EntityManager {
    - _nextEntityID: EntityID
    - _entities: unordered_map<EntityID, shared_ptr<Entity>>
    - _signatures: unordered_map<EntityID, Signature>
    - _componentManager: shared_ptr<ComponentManager>
    + createEntity(): shared_ptr<Entity>
    + destroyEntity(entityID: EntityID): void
    + onComponentAdded<T>(entityID: EntityID): void
    + onComponentRemoved<T>(entityID: EntityID): void
    + getEntitiesWithSignature(signature: Signature): vector<shared_ptr<Entity>>
    + getEntity(entityID: EntityID): shared_ptr<Entity>
  }

  ' System management
  class SystemManager {
    - _systems: vector<shared_ptr<ISystem>>
    - _systemMap: unordered_map<type_index, shared_ptr<ISystem>>
    + registerSystem<T>(): shared_ptr<T>
    + getSystem<T>(): shared_ptr<T>
    + addSystem(system: shared_ptr<ISystem>): void
    + update(deltaTime: float): void
  }

  ' Event management
  class EventManager {
    - _handlers: unordered_map<EventId, vector<HandlerFunction>>
    + subscribe<EventType>(handler: function): void
    + emit<EventType>(event: EventType): void
  }

  ' Resource management
  class ResourceManager {
    - _resources: unordered_map<string, shared_ptr<void>>
    + load<T>(name: string, filename: string): shared_ptr<T>
    + get<T>(name: string): shared_ptr<T>
  }

  ' Scene management
  class Scene {
    - _componentManager: shared_ptr<ComponentManager>
    - _entityManager: shared_ptr<EntityManager>
    - _systemManager: shared_ptr<SystemManager>
    - _eventManager: shared_ptr<EventManager>
    + initialize(): void
    + load(filename: string): void
    + save(filename: string): void
    + update(deltaTime: float): void
    + getEntityManager(): shared_ptr<EntityManager>
    + getComponentManager(): shared_ptr<ComponentManager>
    + getSystemManager(): shared_ptr<SystemManager>
    + getEventManager(): shared_ptr<EventManager>
  }

  ' Vector utilities
  class "Vec2<T>" {
    + x: T
    + y: T
    + Vec2()
    + Vec2(x_val: T, y_val: T)
    + operator+(): Vec2<T>
    + operator-(): Vec2<T>
    + operator*(): Vec2<T>
    + dot(): T
    + magnitude(): T
    + normalize(): Vec2<T>
  }

  class "Vec3<T>" {
    + x: T
    + y: T
    + z: T
    + Vec3()
    + Vec3(x_val: T, y_val: T, z_val: T)
    + operator+(): Vec3<T>
    + operator-(): Vec3<T>
    + operator*(): Vec3<T>
    + dot(): T
    + cross(): Vec3<T>
    + magnitude(): T
    + normalize(): Vec3<T>
  }

  ' Relationships
  IComponentPool <|.. "ComponentPool<T>"

  ComponentManager o-- "ComponentPool<T>"

  Entity o-- ComponentManager

  EntityManager o-- Entity
  EntityManager o-- ComponentManager

  SystemManager o-- ISystem

  Scene o-- ComponentManager
  Scene o-- EntityManager
  Scene o-- SystemManager
  Scene o-- EventManager
}

package "Game Implementation" {
  ' Component examples
  struct "PositionComponent" {
    + x: float
    + y: float
  }

  struct "RenderComponent" {
    + textureName: string
    + width: float
    + height: float
    + layer: int
  }

  ' System examples
  class "MovementSystem" {
    - _entities: vector<shared_ptr<Entity>>
    - _entityManager: shared_ptr<EntityManager>
    + update(deltaTime: float): void
    + processEntities(): void
  }

  class "RenderSystem" {
    - _entities: vector<shared_ptr<Entity>>
    - _resourceManager: shared_ptr<ResourceManager>
    + update(deltaTime: float): void
    + processEntities(): void
    + render(): void
  }

  class "CollisionSystem" {
    - _entities: vector<shared_ptr<Entity>>
    - _eventManager: shared_ptr<EventManager>
    + update(deltaTime: float): void
    + processEntities(): void
    + checkCollisions(): void
  }

  ' Event examples
  class "CollisionEvent" {
    + entity1: EntityID
    + entity2: EntityID
    + position: Vec2<float>
    + normal: Vec2<float>
  }

  class "GameScene" {
    + createPlayer(x: float, y: float): shared_ptr<Entity>
    + createEnemy(x: float, y: float, health: float): shared_ptr<Entity>
    + createObstacle(x: float, y: float, width: float, height: float): shared_ptr<Entity>
    + initialize(): void
    + loadLevel(levelName: string): void
  }

  ISystem <|.. MovementSystem
  ISystem <|.. RenderSystem
  ISystem <|.. CollisionSystem

  GameScene --|> Scene

  MovementSystem --> "PositionComponent"
  RenderSystem --> "RenderComponent"
  CollisionSystem --> "PositionComponent"

  CollisionSystem ..> CollisionEvent : emits
}

' Cross-package relationships
GameScene o-- ResourceManager
RenderSystem o-- ResourceManager

"PositionComponent" --> "Vec2<T>" : uses

@enduml
