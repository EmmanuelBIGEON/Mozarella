#pragma once

#include <glm/ext.hpp>

#include "Cube.h"
#include "Rectangle.h"

class ObjectFactory 
{
    public: 
        static Cube* CreateCube(const glm::vec3& position);
        static Rectangle* CreateRectangle();
};