#include "TexturedCube.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "Assets.h"
#include "stb_image.h"


TexturedCube::TexturedCube(const glm::vec3& position) : GraphicObject(position),
_computed(false), _VAO(0), _VBO(0), _texture(0), _rotating(false) , _vertices(nullptr), _scale(1.0f), _stencilMode(false)
{
    _textureName = assets::Texture::Texture_Cube;
}

TexturedCube::~TexturedCube()
{
    if(_vertices) delete _vertices;
}


void TexturedCube::ToggleRotation()
{
    _rotating = !_rotating;
}

void TexturedCube::SetTextureID(assets::Texture textureName)
{
    _textureName = textureName;
}

void TexturedCube::ApplyScale(float scale)
{
    _scale = scale;

    // No recomputation needed.
    // Instead just recalcule the model.
    _model = glm::mat4(1.0f);
    _model = glm::translate(_model, _position);
    _model = glm::scale(_model, glm::vec3(_scale, _scale, _scale));
}

void TexturedCube::EnableStencilMode()
{
    _stencilMode = true;
}

void TexturedCube::Compute()
{
    if(_computed) return;

    _model = glm::mat4(1.0f);
    _model = glm::translate(_model, _position);
    _model = glm::scale(_model, glm::vec3(_scale, _scale, _scale));

    _vertices = new float[30*6] {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*30*6, _vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    auto shader = Shader::GetShader(SHADER_BASE);
    shader->Use();
    shader->SetInt("texture1", 0);

    _computed = true;
}

void TexturedCube::Render()
{
    if(_stencilMode)
    {
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
    }

    auto shader = Shader::GetShader(SHADER_BASE);
    shader->Use();


    Assets::Bind(_textureName, 0);
    glBindVertexArray(_VAO);
    
    if(_rotating)
    {
        auto model = glm::rotate(_model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 1.0f));
        shader->SetMat4("model", model);
    }else
    {
        shader->SetMat4("model", _model);
    }

    glDrawArrays(GL_TRIANGLES, 0, 36);

    if(_stencilMode)
    {
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);

        auto shader = Shader::GetShader(SHADER_SIMPLEMESH);
        shader->Use();
        
        if(_rotating)
        {
            auto model = glm::rotate(_model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 1.0f));
            model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
            shader->SetMat4("model", model);
        }else 
        {
            auto model = glm::scale(_model, glm::vec3(1.1f, 1.1f, 1.1f));
            shader->SetMat4("model", model);
        }

        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);

        glEnable(GL_DEPTH_TEST);
    }
}
