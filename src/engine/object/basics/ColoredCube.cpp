#include "ColoredCube.h"

#include "Shader.h"
#include <glad/glad.h>


ColoredCube::ColoredCube(const glm::vec3& position, const glm::vec3& color)
    : GraphicObject(), _position(position), _color(color), _model(1.0f), _colourGroup(nullptr), _width(2.0f), 
    _computed(false), _vertices(nullptr)
{
    _model = glm::translate(_model, _position);
}

ColoredCube::ColoredCube(const glm::vec3& position, float width, const glm::vec3& color)
    : GraphicObject(), _position(position), _color(color), _width(width), _model(1.0f), _colourGroup(nullptr), 
    _computed(false), _vertices(nullptr)
{
    _model = glm::translate(_model, _position);
}

ColoredCube::~ColoredCube()
{
}

void ColoredCube::SetWidth(float width)
{
    _width = width;
    _computed = false; 
}

void ColoredCube::Assign(ColourGroup* colourGroup)
{
    _colourGroup = colourGroup;
}

void ColoredCube::Compute()
{
    if(_computed) return;
    if(_vertices) delete _vertices;
    _computed = true;

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

void ColoredCube::Render()
{
    auto shader = Shader::GetShader(SHADER_SIMPLEMESH);
    shader->Use();
    glBindVertexArray(_VAO);

    shader->SetMat4("model", _model);
    if(_colourGroup)
        shader->SetVec4("color", {_colourGroup->color, 1.0f});
    else 
        shader->SetVec4("color", {_color, 1.0f});
        
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

