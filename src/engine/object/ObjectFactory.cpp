#include "ObjectFactory.h"

Cube* ObjectFactory::CreateCube(const glm::vec3& position)
{
    return new Cube(position);
}

Rectangle* ObjectFactory::CreateRectangle()
{
    return new Rectangle();
}

Rectangle* ObjectFactory::CreateRectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4)
{
    return new Rectangle(p1, p2, p3, p4);
}

Sphere* ObjectFactory::CreateSphere(const glm::vec3& position)
{
    return new Sphere(position);
}

Sphere* ObjectFactory::CreateSphere(const glm::vec3& position, unsigned int subdivisionCount)
{
    return new Sphere(position, subdivisionCount);
}