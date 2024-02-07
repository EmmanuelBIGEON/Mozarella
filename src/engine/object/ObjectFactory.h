#pragma once

#include <glm/ext.hpp>

#include "Cube.h"
#include "ColoredCube.h"
#include "Rectangle.h"
#include "Sphere.h"

class ObjectFactory 
{
    public: 
        static Cube* CreateCube(const glm::vec3& position);
        static ColoredCube* CreateColoredCube(const glm::vec3& position, ColourGroup* colourgroup = nullptr);
        static ColoredCube* CreateColoredCube(const glm::vec3& position, float width, ColourGroup* colourgroup = nullptr);
        static Rectangle* CreateRectangle();
        static Rectangle* CreateRectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4);
        static Sphere* CreateSphere(const glm::vec3& position);
        static Sphere* CreateSphere(const glm::vec3& position, unsigned int subdivisionCount);
};