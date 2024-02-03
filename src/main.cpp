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
    
    auto window = Window::Create(1000,800);
    // auto scene = SceneFactory::CreateColorScene({1.0f, 0.0f, 0.0f});
    auto scene = SceneFactory::CreateCubeScene();
    window->SetScene(scene);
    mozarella->Add(window);

    while(mozarella->Run());

    return 0;
}