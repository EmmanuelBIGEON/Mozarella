#include "SceneColor.h"

#include "ViewFactory.h"

#include <glad/glad.h>

SceneColor::SceneColor(const glm::vec3& pColor)
{
    Add(ViewFactory::CreateColorView(pColor));
}

SceneColor::~SceneColor()
{
}

void SceneColor::Render()
{

    for(const auto& view : _views)
    {
        if(!view->Render())
        {
            _views.erase(std::remove(_views.begin(), _views.end(), view), _views.end());
            break;
        }
    }
}
