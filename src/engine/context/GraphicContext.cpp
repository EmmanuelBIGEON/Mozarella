#include "GraphicContext.h"

#include <algorithm>
#include <glm/ext.hpp>

GraphicContext::GraphicContext()
{
}

GraphicContext::~GraphicContext()
{
}

void GraphicContext::AddObject(GraphicObject* pObject, bool hasTransparency)
{
    _objects.push_back(pObject);

    if(hasTransparency)
        _transparencyObjects.push_back(pObject);
    else 
        _opaquesObjects.push_back(pObject);
}

void GraphicContext::RemoveObject(GraphicObject* pObject)
{
    _objects.erase(std::remove(_objects.begin(), _objects.end(), pObject), _objects.end());

    auto it = std::find(_transparencyObjects.begin(), _transparencyObjects.end(), pObject);
    if(it != _transparencyObjects.end())
        _transparencyObjects.erase(it);

    auto itOpaque = std::find(_opaquesObjects.begin(), _opaquesObjects.end(), pObject);
    if(itOpaque != _opaquesObjects.end())
        _opaquesObjects.erase(itOpaque);
}

void GraphicContext::Sort(const glm::vec3& cameraPosition)
{
    _objects.clear();

    for(auto &obj : _opaquesObjects)
        _objects.push_back(obj);

    std::sort(_transparencyObjects.begin(), _transparencyObjects.end(), [cameraPosition](GraphicObject* obj1, GraphicObject* obj2)
    {
        return glm::length(cameraPosition - obj1->GetPosition()) > glm::length(cameraPosition - obj2->GetPosition());
    });

    for(auto &obj : _transparencyObjects)
        _objects.push_back(obj);
}

void GraphicContext::Render()   
{
    for(auto &obj : _objects)
    {
        obj->Compute();
        obj->Render();
    }
}
