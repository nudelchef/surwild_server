#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "Direction.h"

class Entity {
public:
    Entity();

    virtual ~Entity();

    std::string textureString;

    Direction movementDirection;

    uint32_t entityId;

    uint32_t tilePositionX;
    uint32_t tilePositionY;

    uint32_t x;
    uint32_t y;

protected:

private:
};

#endif // ENTITY_H
