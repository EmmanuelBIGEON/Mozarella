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
            context->AddObject(cube);
            }
        }
    }   

    

    // On ajoute une source de lumière
    _lightSource = ObjectFactory::CreateLightSource({-10.0f, 1.0f, 0.0f}, {0.445f, 0.741f, 0.848f});
    context->AddObject(_lightSource);

    // On ajoute l'éditeur de couleur
    _editor = new ColorEditor();
    _editor->Add("Cubes's color", _groupColor);
    _editor->Add("Light's color", _lightSource->Color());

    // Add a camera to the scene.
    _myView->EnableCamera();
    _myView->GetCamera()->SetPosition({9.0f, 9.0f, 46.0f});

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
    auto shadermesh = Shader::GetShader(SHADER_MESH);   
    shadermesh->Use();
    shadermesh->SetVec3("lightColor", _lightSource->Color());
    shadermesh->SetVec3("lightPos", _lightSource->Position());
    shadermesh->SetVec3("viewPos", _myView->GetCamera()->Position);

    for(const auto& view : _views)
    {
        if(!view->Render())
        {
            _views.erase(std::remove(_views.begin(), _views.end(), view), _views.end());
            break;
        }
    }
    _editor->Display();
}
