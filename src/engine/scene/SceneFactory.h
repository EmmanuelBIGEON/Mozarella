#pragma once 

#include "Scene.h"

#include <glm/ext.hpp>

class SceneFactory
{
    public:
        static Scene* CreateDefaultScene();
        static Scene* CreateColorScene(const glm::vec3& pColor);
        static Scene* CreateCubeScene();
};