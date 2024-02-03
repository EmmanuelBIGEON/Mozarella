#include "ObjectFactory.h"

Cube* ObjectFactory::CreateCube(const glm::vec3& position)
{
    return new Cube(position);
}