#include "GraphicObject.h"

GraphicObject::GraphicObject(const glm::vec3& position) : _position(position)
{
}

GraphicObject::~GraphicObject()
{
}

void GraphicObject::SetPosition(const glm::vec3& position)
{
    _position = position;
}

const glm::vec3& GraphicObject::GetPosition()
{
    return _position;
}

glm::vec3& GraphicObject::Position()
{
    return _position;
}

void GraphicObject::Compute()
{
}

void GraphicObject::Render()
{
}
