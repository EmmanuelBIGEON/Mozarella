#include "LightSource.h"

#include "Shader.h"
#include <glad/glad.h>

LightSource::LightSource(const glm::vec3& position, const glm::vec3& color) : GraphicObject(position), 
    _color(color), _model(1.0f), _width(0.8f), 
    _computed(false), _vertices(nullptr), _VAO(0), _VBO(0)
{
}

LightSource::~LightSource()
{
    if(_vertices) delete _vertices;
}

void LightSource::SetWidth(float width)
{
    _width = width;
    _computed = false; 
}

glm::vec3& LightSource::Color()
{
    return _color;
}

void LightSource::Compute()
{ 
    if(_computed) return;
    if(_vertices) delete _vertices;
    _computed = true;
    _model = glm::mat4(1.0f);
    _model = glm::translate(_model, _position);

    _vertices = new float[18*6] {
        -_width, -_width, -_width,
         _width, -_width, -_width,
         _width,  _width, -_width,
         _width,  _width, -_width,
        -_width,  _width, -_width,
        -_width, -_width, -_width,

        -_width, -_width,  _width,
         _width, -_width,  _width,
         _width,  _width,  _width,
         _width,  _width,  _width,
        -_width,  _width,  _width,
        -_width, -_width,  _width,

        -_width,  _width,  _width,
        -_width,  _width, -_width,
        -_width, -_width, -_width,
        -_width, -_width, -_width,
        -_width, -_width,  _width,
        -_width,  _width,  _width,

         _width,  _width,  _width,
         _width,  _width, -_width,
         _width, -_width, -_width,
         _width, -_width, -_width,
         _width, -_width,  _width,
         _width,  _width,  _width,

        -_width, -_width, -_width,
         _width, -_width, -_width,
         _width, -_width,  _width,
         _width, -_width,  _width,
        -_width, -_width,  _width,
        -_width, -_width, -_width,

        -_width,  _width, -_width,
         _width,  _width, -_width,
         _width,  _width,  _width,
         _width,  _width,  _width,
        -_width,  _width,  _width,
        -_width,  _width, -_width
    };

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*18*6, _vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

void LightSource::Render()
{
    auto shader = Shader::GetShader(SHADER_SIMPLEMESH);
    shader->Use();
    glBindVertexArray(_VAO);
    shader->SetMat4("model", _model);
    shader->SetVec3("color", _color);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
