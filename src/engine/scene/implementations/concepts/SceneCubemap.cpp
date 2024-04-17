#include "SceneCubemap.h"

#include "Sphere.h"

#include "ViewFactory.h"
#include "GraphicContext.h"
#include "Shader.h"
#include "ObjectFactory.h"
#include "TextureLoader.h"

SceneCubemap::SceneCubemap() : _VAO(0), _VBO(0)
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

    // Add a camera to the scene.
    _myView->EnableCamera();
    _myView->GetCamera()->SetPosition({0.0f, 0.0f, 20.0f});

    // Init the skybox VAO and VBO.
    InitSkybox();

    _myView->SetContext(context);
    Add(_myView);
}

SceneCubemap::~SceneCubemap()
{
}

void SceneCubemap::Process(Event& event)
{
    _myView->UpdateCamera(event);
}

void SceneCubemap::Render()
{
    for(const auto& view : _views)
    {
        if(!view->Render())
        {
            _views.erase(std::remove(_views.begin(), _views.end(), view), _views.end());
            break;
        }
    }

    DrawSkybox();
}

void SceneCubemap::InitSkybox()
{
    
    _vertices = new float[18*6] {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18*6, _vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    auto shader = Shader::GetShader(SHADER_SKYBOX);
    shader->Use();
    shader->SetInt("skybox", 0);
}

void SceneCubemap::DrawSkybox()
{

    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    auto shader = Shader::GetShader(SHADER_SKYBOX);
    shader->Use();

    glBindVertexArray(_VAO);
    Assets::Bind(assets::Texture::Texture_Skybox, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default
}