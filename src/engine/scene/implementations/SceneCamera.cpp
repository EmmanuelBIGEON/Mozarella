#include "SceneCamera.h"

#include "ViewFactory.h"
#include "ObjectFactory.h"
#include "GraphicContext.h"

SceneCamera::SceneCamera()
{
    _myView = ViewFactory::CreateSimple3DView();
    auto context = std::make_shared<GraphicContext>();

    // Add a rotating cube to the scene.
    auto cube = ObjectFactory::CreateCube({0.0f, 0.0f, 2.0f});
    cube->SetTextureID(assets::Texture::Texture_Cube2);
    cube->ToggleRotation();
    context->AddObject(cube);

    // Add a rotating cube to the scene.
    auto cube2 = ObjectFactory::CreateCube({0.0f, 0.0f, 0.0f});
    cube2->SetTextureID(assets::Texture::Texture_Cube3);
    cube2->ToggleRotation();
    context->AddObject(cube2);

    // Add a plane.
    // glm::vec3 p1 = glm::vec3(10.0f, -1.0f, 10.0f);
    // glm::vec3 p2 = glm::vec3(-10.0f, -1.0f, 10.0f);
    // glm::vec3 p3 = glm::vec3(-10.0f, -1.0f, -10.0f);
    // glm::vec3 p4 = glm::vec3(10.0f, -1.0f, -10.0f);
    // auto plane = ObjectFactory::CreateRectangle(p1, p2,  p3, p4);
    // context->AddObject(plane);

    // Add a camera to the scene.
    _myView->EnableCamera();

    _myView->SetContext(context);
    Add(_myView);
}

SceneCamera::~SceneCamera()
{
}

void SceneCamera::Process(Event& event)
{
    _myView->UpdateCamera(event);
}

void SceneCamera::Render()
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
