#include "SceneCube.h"

#include <memory>

#include "ViewFactory.h"
#include "ObjectFactory.h"
#include "GraphicContext.h"

SceneCube::SceneCube()
{
    auto view = ViewFactory::CreateSimple3DView();
    auto context = std::make_shared<GraphicContext>();
    _cube = ObjectFactory::CreateCube({0.0f, 0.0f, 0.0f});
    context->AddObject(_cube);

    _cube->ToggleRotation();

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

void SceneCube::Process(Event& event)
{
    if(event.GetEventType() == EventType::EVENT_KEY)
    {
        KeyEvent* keyEvent = (KeyEvent*)&event;
        if(keyEvent->GetKeyType() == EventKeyType::EVENT_KEY_PRESSED)
        {
            KeyPressedEvent* keyPressedEvent = (KeyPressedEvent*)&event;

            if(keyPressedEvent->key == Key_S)
            {
                _cube->ToggleRotation();
            }
        }
    }
}