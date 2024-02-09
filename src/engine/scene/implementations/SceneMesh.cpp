#include "SceneMesh.h"

#include "ViewFactory.h"
#include "Model.h"
#include "GraphicContext.h"
#include "ObjectFactory.h"
#include "Shader.h"

#include <stb_image.h>

SceneMesh::SceneMesh()
{
    _myView = ViewFactory::CreateSimple3DView();
    auto context = std::make_shared<GraphicContext>();

    // Add a model to the scene
    auto model = ObjectFactory::LoadModel("../models/baker_and_the_bridge.glb");
    context->AddObject(model);

    // Add a camera to the scene.
    _myView->EnableCamera();

    // Display the default background'
    _myView->EnableBackground();
    
    _myView->SetContext(context);

    _myView->GetCamera()->Position = {-9.0f, 15.0f, 51.0f};
    Add(_myView);
}

SceneMesh::~SceneMesh()
{
}

void SceneMesh::Process(Event& event)
{
    _myView->UpdateCamera(event);
}

void SceneMesh::Render()
{
    
    // be sure to activate shader when setting uniforms/drawing objects
    auto shader = Shader::GetShader(SHADER_MATERIAL);
    shader->Use();
    shader->SetVec3("light.position", {1.2f, 1.0f, 2.0f});
    shader->SetVec3("viewPos", _myView->GetCamera()->Position);

    // light properties
    glm::vec3 lightColor;
    lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0));
    lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7));
    lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3));
    glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
    shader->SetVec3("light.ambient", ambientColor);
    shader->SetVec3("light.diffuse", diffuseColor);
    shader->SetVec3("light.specular", {1.0f, 1.0f, 1.0f});
    shader->SetVec3("material.ambient", {1.0f, 0.5f, 0.31f});
    shader->SetVec3("material.diffuse", {1.0f, 0.5f, 0.31f});
    shader->SetVec3("material.specular", {0.5f, 0.5f, 0.5f}); // specular lighting doesn't have full effect on this object's material
    shader->SetFloat("material.shininess", 32.0f);

    for(const auto& view : _views)
    {
        if(!view->Render())
        {
            _views.erase(std::remove(_views.begin(), _views.end(), view), _views.end());
            break;
        }
    }
}
