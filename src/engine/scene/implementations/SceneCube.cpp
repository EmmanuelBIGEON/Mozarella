#include "SceneCube.h"

#include <memory>

#include "ViewFactory.h"
#include "ObjectFactory.h"
#include "GraphicContext.h"

SceneCube::SceneCube()
{
    auto view = ViewFactory::CreateSimple3DView();
    auto context = std::make_shared<GraphicContext>();
    context->AddObject(ObjectFactory::CreateCube({0.0f, 0.0f, 0.0f}));

    view->SetContext(context);
    Add(view);
}

SceneCube::~SceneCube()
{
}

void SceneCube::Render()
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
