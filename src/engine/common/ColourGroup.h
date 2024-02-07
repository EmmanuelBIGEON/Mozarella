#pragma once 

#include <glm/ext.hpp>

struct ColourGroup
{
    glm::vec3 color;

    ColourGroup(const glm::vec3& pcolor) : color(pcolor) {}
    glm::vec3& Color() { return color; }
};