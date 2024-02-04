#include "SceneCamera.h"

#include "ViewFactory.h"
#include "ObjectFactory.h"
#include "GraphicContext.h"

SceneCamera::SceneCamera()
{
    _myView = ViewFactory::CreateSimple3DView();
    auto context = std::make_shared<GraphicContext>();

    // Add a rotating cube to the scene.
    auto cube = ObjectFactory::CreateCube({0.0f, 0.0f, 0.0f});
    cube->ToggleRotation();
    context->AddObject(cube);

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

    std::cout << "iai" << std::endl;
    if(event.GetEventType() == EventType::EVENT_KEY)
    {
        KeyEvent* keyEvent = (KeyEvent*)&event;
        if(keyEvent->GetKeyType() == EventKeyType::EVENT_KEY_PRESSED)
        {
            KeyPressedEvent* keyPressedEvent = (KeyPressedEvent*)&event;
            std::cout << "key : " << keyPressedEvent->key << std::endl;
        }
    }
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
