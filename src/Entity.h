#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "Direction.h"

class Entity
{
public:
    Entity();
    virtual ~Entity();

    std::string texture;

    Direction movementDirection;

    unsigned int entityId;

    unsigned short tilePositionX;
    unsigned short tilePositionY;

    unsigned short x;
    unsigned short y;

protected:

private:
};

#endif // ENTITY_H
