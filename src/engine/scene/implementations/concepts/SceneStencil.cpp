#include "SceneStencil.h"

#include <memory>

#include "ViewFactory.h"
#include "ObjectFactory.h"
#include "GraphicContext.h"

SceneStencil::SceneStencil()
{
    _myView = ViewFactory::CreateSimple3DView();
    auto context = std::make_shared<GraphicContext>();

    // Add a plane.
    glm::vec3 p1 = glm::vec3(10.0f, -1.0f, 10.0f);
    glm::vec3 p2 = glm::vec3(-10.0f, -1.0f, 10.0f);
    glm::vec3 p3 = glm::vec3(-10.0f, -1.0f, -10.0f);
    glm::vec3 p4 = glm::vec3(10.0f, -1.0f, -10.0f);
    auto plane = ObjectFactory::CreateRectangle(p1, p2,  p3, p4);
    context->AddObject(plane);
    
    _cube = ObjectFactory::CreateTexturedCube({0.0f, 0.0f, 0.0f});
    _cube->SetTextureID(assets::Texture::Texture_Background);
    _cube->EnableStencilMode();
    context->AddObject(_cube);


    // Add a camera to the scene.
    _myView->EnableCamera();

    // Set stencil color
    _color = glm::vec3({1.0f, 1.0f, 1.0f});

    // On ajoute l'éditeur de couleur
    _editor = new ColorEditor();
    _editor->Add("Stencil's color", _color);

    _myView->SetContext(context);
    Add(_myView);
}

SceneStencil::~SceneStencil()
{
}

void SceneStencil::Process(Event& event)
{
    _myView->UpdateCamera(event);

    if(event.GetEventType() == EventType::EVENT_KEY)
    {
        KeyEvent* keyEvent = (KeyEvent*)&event;
        if(keyEvent->GetKeyType() == EventKeyType::EVENT_KEY_PRESSED)
        {
            KeyPressedEvent* keyPressedEvent = (KeyPressedEvent*)&event;

            if(keyPressedEvent->key == Key_U)
            {
                _cube->ToggleRotation();
            }
        }
    }
}

void SceneStencil::Render()
{
    auto shader = Shader::GetShader(SHADER_SIMPLEMESH);
    shader->Use();
    shader->SetVec3("color", _color);
    
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
