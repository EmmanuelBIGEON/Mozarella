#pragma once 

#include "Scene.h"

#include <glm/ext.hpp>

class SceneFactory
{
    public:
        static Scene* CreateDefaultScene();
        static Scene* CreateColorScene(const glm::vec3& pColor);
        static Scene* CreateCubeScene();
        static Scene* CreateCameraScene();
        static Scene* CreateMeshScene();
        static Scene* CreateLightScene();
        static Scene* CreateSphereScene();
        static Scene* CreateEditScene();
        static Scene* CreateStencilScene();
        static Scene* CreateTransparencyScene();
        static Scene* CreateFramebufferScene();
        static Scene* CreateCubemapScene();
};