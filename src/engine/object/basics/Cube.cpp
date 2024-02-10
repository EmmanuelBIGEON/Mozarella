#include "Cube.h"

#include "Shader.h"
#include <glad/glad.h>


Cube::Cube(const glm::vec3& position, const glm::vec3& color)
    : GraphicObject(position), _color(color), _model(1.0f), _width(2.0f), _alpha(1.0f),
    _computed(false), _vertices(nullptr), _VAO(0), _VBO(0), _colourGroup(nullptr)
{
}

Cube::Cube(const glm::vec3& position, float width, const glm::vec3& color)
    : GraphicObject(position), _color(color), _model(1.0f),  _width(2.0f), _alpha(1.0f),
    _computed(false), _vertices(nullptr), _VAO(0), _VBO(0), _colourGroup(nullptr)
{
}

Cube::~Cube()
{
}

void Cube::SetTransparency(float alpha)
{
    _alpha = alpha;
}

void Cube::Assign(ColourGroup* colourGroup)
{
    _colourGroup = colourGroup;
}

void Cube::Compute()
{
    if(_computed) return;
    if(_vertices) delete _vertices;

    _computed = true;
    _model = glm::mat4(1.0f);
    _model = glm::translate(_model, _position);

    _vertices = new float[36*6] {
        -_width, -_width, -_width, 0.0f, 0.0f, -1.0f,
         _width, -_width, -_width, 0.0f, 0.0f, -1.0f,
         _width,  _width, -_width, 0.0f, 0.0f, -1.0f,
         _width,  _width, -_width, 0.0f, 0.0f, -1.0f,
        -_width,  _width, -_width, 0.0f, 0.0f, -1.0f,
        -_width, -_width, -_width, 0.0f, 0.0f, -1.0f,

        -_width, -_width,  _width, 0.0f, 0.0f, 1.0f,
         _width, -_width,  _width, 0.0f, 0.0f, 1.0f,
         _width,  _width,  _width, 0.0f, 0.0f, 1.0f,
         _width,  _width,  _width, 0.0f, 0.0f, 1.0f,
        -_width,  _width,  _width, 0.0f, 0.0f, 1.0f,
        -_width, -_width,  _width, 0.0f, 0.0f, 1.0f,

        -_width,  _width,  _width, -1.0f, 0.0f, 0.0f,
        -_width,  _width, -_width, -1.0f, 0.0f, 0.0f,
        -_width, -_width, -_width, -1.0f, 0.0f, 0.0f,
        -_width, -_width, -_width, -1.0f, 0.0f, 0.0f,
        -_width, -_width,  _width, -1.0f, 0.0f, 0.0f,
        -_width,  _width,  _width, -1.0f, 0.0f, 0.0f,

         _width,  _width,  _width, 1.0f, 0.0f, 0.0f,
         _width,  _width, -_width, 1.0f, 0.0f, 0.0f,
         _width, -_width, -_width, 1.0f, 0.0f, 0.0f,
         _width, -_width, -_width, 1.0f, 0.0f, 0.0f,
         _width, -_width,  _width, 1.0f, 0.0f, 0.0f,
         _width,  _width,  _width, 1.0f, 0.0f, 0.0f,

        -_width, -_width, -_width, 0.0f, -1.0f, 0.0f,
         _width, -_width, -_width, 0.0f, -1.0f, 0.0f,
         _width, -_width,  _width, 0.0f, -1.0f, 0.0f,
         _width, -_width,  _width, 0.0f, -1.0f, 0.0f,
        -_width, -_width,  _width, 0.0f, -1.0f, 0.0f,
        -_width, -_width, -_width, 0.0f, -1.0f, 0.0f,

        -_width,  _width, -_width, 0.0f, 1.0f, 0.0f,
         _width,  _width, -_width, 0.0f, 1.0f, 0.0f,
         _width,  _width,  _width, 0.0f, 1.0f, 0.0f,
         _width,  _width,  _width, 0.0f, 1.0f, 0.0f,
        -_width,  _width,  _width, 0.0f, 1.0f, 0.0f,
        -_width,  _width, -_width, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*36*6, _vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}

void Cube::Render()
{
    auto shader = Shader::GetShader(SHADER_MESH);
    shader->Use();
    glBindVertexArray(_VAO);

    shader->SetMat4("model", _model);
    if(_colourGroup)
        shader->SetVec4("objectColor", {_colourGroup->color, _alpha});
    else 
        shader->SetVec4("objectColor", {_color, _alpha});
        
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
