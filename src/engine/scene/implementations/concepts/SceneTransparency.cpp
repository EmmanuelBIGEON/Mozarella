#include "SceneTransparency.h"

#include <memory>

#include "ViewFactory.h"
#include "ObjectFactory.h"

SceneTransparency::SceneTransparency()
{
    _myView = ViewFactory::CreateSimple3DView();
    _myContext = std::make_shared<GraphicContext>();

    // On génère une batterie de cube coloré.
    _groupColor = new ColourGroup({0.744f, 0.559f, 0.431f});

    auto width = 2.0f;
    for(int i = 0 ; i < 5; i++)
    {
        for(int j = 0 ; j < 5; j++)
        {
            for(int k = 0 ; k < 5; k++)
            {
                auto cube = ObjectFactory::CreateCube({i * (width*2 + 2.0f), 
                                                            j * (width*2 + 2.0f), 
                                                            k * (width*2 + 2.0f)},
                                                            _groupColor);
                cube->SetTransparency(0.5f);
                _myContext->AddObject(cube, true);
            }
        }
    }   

    // Add a camera to the scene.
    _myView->EnableCamera();

    _myView->SetContext(_myContext);
    Add(_myView);
}

SceneTransparency::~SceneTransparency()
{
}

void SceneTransparency::Render()
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

void SceneTransparency::Process(Event& event)
{
    _myView->UpdateCamera(event);
    _myContext->Sort(_myView->GetCamera()->Position);
}