#include "SceneLight.h"

#include "Sphere.h"

#include "ViewFactory.h"
#include "GraphicContext.h"
#include "Shader.h"
#include "ObjectFactory.h"


SceneLight::SceneLight()
{
    _myView = ViewFactory::CreateSimple3DView();
    auto context = std::make_shared<GraphicContext>();
    
    // Add a camera to the scene.
    _myView->EnableCamera();

    _myView->SetContext(context);
    Add(_myView);
}

SceneLight::~SceneLight()
{
}

void SceneLight::Process(Event& event)
{
    _myView->UpdateCamera(event);
}

void SceneLight::Render()
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
