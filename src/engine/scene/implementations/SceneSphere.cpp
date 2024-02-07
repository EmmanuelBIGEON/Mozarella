#include "SceneSphere.h"

#include "Sphere.h"

#include "ViewFactory.h"
#include "GraphicContext.h"
#include "Shader.h"
#include "ObjectFactory.h"


SceneSphere::SceneSphere()
{
    _myView = ViewFactory::CreateSimple3DView();
    auto context = std::make_shared<GraphicContext>();

    auto sphere = ObjectFactory::CreateSphere({0.0f, 0.0f, 2.0f});
    auto sphere2 = ObjectFactory::CreateSphere({0.0f, 0.0f, 8.0f});
    sphere2->SetWireFrameMode();
    context->AddObject(sphere);
    context->AddObject(sphere2);
    
    auto sphere3 = ObjectFactory::CreateSphere({0.0f, 7.0f, 2.0f}, 5);
    auto sphere4 = ObjectFactory::CreateSphere({0.0f, 7.0f, 8.0f}, 5);
    sphere4->SetWireFrameMode();
    context->AddObject(sphere3);
    context->AddObject(sphere4);

    // Add a camera to the scene.
    _myView->EnableCamera();
    _myView->GetCamera()->SetPosition({0.0f, 0.0f, 20.0f});

    _myView->SetContext(context);
    Add(_myView);
}

SceneSphere::~SceneSphere()
{
}

void SceneSphere::Process(Event& event)
{
    _myView->UpdateCamera(event);
}

void SceneSphere::Render()
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
