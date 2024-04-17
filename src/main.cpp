#include <iostream>

#include "Engine.h"
#include "Window.h"
#include "SceneFactory.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char** argv)
{

    Engine* mozarella = new Engine();
    mozarella->Init();
    
    auto window = Window::Create(1400,1000);
    // auto scene = SceneFactory::CreateColorScene({1.0f, 0.0f, 0.0f});
    // auto scene = SceneFactory::CreateCubeScene();
    auto scene = SceneFactory::CreateMeshScene();
    // auto scene = SceneFactory::CreateCameraScene();
    // auto scene = SceneFactory::CreateLightScene();
    // auto scene = SceneFactory::CreateSphereScene();
    // auto scene = SceneFactory::CreateEditScene();
    // auto scene = SceneFactory::CreateStencilScene();
    // auto scene = SceneFactory::CreateTransparencyScene();
    // auto scene = SceneFactory::CreateFramebufferScene();
    // auto scene = SceneFactory::CreateCubemapScene();
    window->SetScene(scene);
    mozarella->Add(window);

    while(mozarella->Run());

    return 0;
}