Before using it, better to know what you'll be playing with...

What is an Entity-Component-System (ECS) ?

An Entity–component–system (ECS) is a software architectural pattern mostly used in video game development for the representation of game world objects.

What's the difference between Entities, Systems and Components ?

Entities:\
    - Players, mobs, structures, and items are entities.\
    - Entities are individual objects or units in the game world. They are abstract and represent things like players, enemies, buildings, or items in the game.\
    - Entities themselves don’t contain behavior or logic. Instead, they are containers for components that hold data (e.g., position, health, texture).\
Example: A player entity will have a PositionComponent, a HealthComponent, a TextureComponent, and so on.

Components:\
    - Components are pieces of data that describe an aspect of an entity. They hold state, like health, position, velocity, or texture, but they don’t contain any logic.\
    - Components are added to entities to give them specific characteristics or behaviors.\
Example: The PositionComponent contains the position data of an entity (e.g., Vec3<float> position), but doesn’t contain the logic to move the entity.

Systems:\
    - Systems are responsible for processing entities based on the components they have.\
    - A system defines behavior or logic and operates on entities that possess certain components.\
    - For example, the MovementSystem operates on entities that have a PositionComponent and a VelocityComponent and updates their positions based on velocity.\
Example: A HealthSystem might process all entities with a HealthComponent, reducing their health over time or handling damage.
