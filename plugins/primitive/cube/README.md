
# `CUBE` EntityConfig

1. [Plugin Description](#description)
2. [Config Example](#config-example)
3. [Config Values](#config-values)

## Plugin Description

create a cube that can go to space.

## Plugin Example

EntityType:
{
    Entity = (
    {
        pos_x = 0;
        pos_y = 0;
        pos_z = 0;
        r = 0;
        g = 0;
        b = 0;
        size = 0; 
        height = 0;
    });
}

## Plugin Values

pos_x, pos_y, pos_z refers to Cube Direction:
- pos_x -> float => for the positon,
- pos_y -> float => for the positon,
- pos_z -> float => for the positon,

"r", "g", "b" refers to Cube Color:
- r -> size_t => value from 0 to 255 for the proportion of red,
- g -> size_t => value from 0 to 255 for the proportion of green,
- b -> size_t => value from 0 to 255 for the proportion of blue,

"size"
- size -> float => for the scale of the object,

"height"
- height -> float => for the scale of the object
