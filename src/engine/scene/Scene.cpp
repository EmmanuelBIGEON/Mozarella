#include "Scene.h"

#include <glad/glad.h>

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Add(View* pView)
{
    _views.push_back(pView);
}

void Scene::Connect(Window* window)
{
    // todo
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
