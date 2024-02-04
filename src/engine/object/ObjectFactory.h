#pragma once

#include <glm/ext.hpp>

#include "Cube.h"
#include "Rectangle.h"

class ObjectFactory 
{
    public: 
        static Cube* CreateCube(const glm::vec3& position);
        static Rectangle* CreateRectangle();
        static Rectangle* CreateRectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4);
};