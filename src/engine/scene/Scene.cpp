#include "Scene.h"

#include <glad/glad.h>

#include "Window.h"

Scene::Scene() : _activeView(nullptr)
{
}

Scene::~Scene()
{
    if(_slot) delete _slot;
}

void Scene::Add(View* pView)
{
    _views.push_back(pView);
    if(!_activeView) _activeView = pView;
}

void Scene::Connect(Window* window)
{
    // On forward les evenements vers la vue.
    _slot = window->OnEvent.Connect([this](Event& event){
        Process(event);
    }); 
}

void Scene::Process(Event& event)
{
    // Do nothing.
}

void Scene::Render()
{
    // On paint en nuance de gris pour montrer qu'il n'y a pas de vue dans la fenetre.
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for(const auto& view : _views)
    {
        if(!view->Render())
        {
            _views.erase(std::remove(_views.begin(), _views.end(), view), _views.end());
            break;
        }
    }
}