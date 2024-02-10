#include "SceneEdit.h"

#include "ViewFactory.h"
#include "ObjectFactory.h"
#include "GraphicContext.h"
#include "QuickEditor.h"
#include "Shader.h"


SceneEdit::SceneEdit()
{
    _myView = ViewFactory::CreateSimple3DView();
    auto context = std::make_shared<GraphicContext>();
    
    // Une lumiere blanche par défaut
    _lightColor = glm::vec3({1.0f, 1.0f, 1.0f});

    // On génère une batterie de cube coloré.
    _groupColor = new ColourGroup({0.0f, 1.0f, 0.0f});

    // On ajoute l'éditeur de couleur
    _editor = new ColorEditor();
    _editor->Add("Cubes's color", _groupColor);
    _editor->Add("Light's color", _lightColor);


    for(int i = 0 ; i < 4; i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            auto cube = ObjectFactory::CreateColoredCube({i * 6.0f, j * 6.0f, 3.0f}, _groupColor);
            context->AddObject(cube);
        }
    }   
    
    // Add a camera to the scene.
    _myView->EnableCamera();
    _myView->GetCamera()->SetPosition({9.0f, 9.0f, 46.0f});

    _myView->SetContext(context);
    Add(_myView);
}

SceneEdit::~SceneEdit()
{
}

void SceneEdit::Process(Event& event)
{
    _myView->UpdateCamera(event);
}

void SceneEdit::Render()
{
    auto shader_simplemesh = Shader::GetShader(SHADER_SIMPLEMESH);
    shader_simplemesh->Use();
    shader_simplemesh->SetVec3("lightColor", _lightColor);

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
