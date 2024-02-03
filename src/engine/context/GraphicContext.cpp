#include "GraphicContext.h"


GraphicContext::GraphicContext()
{
}

GraphicContext::~GraphicContext()
{
}

void GraphicContext::AddObject(GraphicObject* pObject)
{
    _objects.push_back(pObject);
}

void GraphicContext::RemoveObject(GraphicObject* pObject)
{
    _objects.erase(std::remove(_objects.begin(), _objects.end(), pObject), _objects.end());
}

void GraphicContext::Render()
{
    for(auto &obj : _objects)
    {
        obj->Compute();
        obj->Render();
    }
}
