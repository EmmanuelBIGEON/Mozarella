#include "Engine.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Assets.h"


Engine::Engine()
{
}

Engine::~Engine()
{
    _mapWindows.clear();
}

void Engine::Add(Window* pWindow)
{
    if(pWindow)
        _mapWindows.insert(std::make_pair(_mapWindows.size()+1, pWindow));
}

void Engine::Remove(Window* pWindow)
{
    for(const auto& elem : _mapWindows)
    {
        if(elem.second == pWindow)
        {
            _mapWindows.erase(_mapWindows.find(elem.first));
            break;
        }
    } 

}

bool Engine::Run()
{
    if(_mapWindows.empty()) return false;

    for(const auto& pairWindow : _mapWindows)
    {
        if(!pairWindow.second->Render())
        {
            Remove(pairWindow.second);
            break; // the _mapWindows has changed.
        }
    }

    return true;
}

void Engine::Init()
{
    if (!glfwInit()){ std::cout << "Failed glfwInit" << std::endl; return; }
}