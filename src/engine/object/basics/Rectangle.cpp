#include "Rectangle.h"

#include <stb_image.h>
#include <iostream>
#include <glad/glad.h>

#include "Shader.h"

Rectangle::Rectangle(glm::vec3 position, float width, float height) : GraphicObject(),  
_computed(false), _VAO(0), _VBO(0), _texture(0), _vertices(nullptr)
{
    auto tempW = width/2.0f;
    auto tempH = height/2.0f;
    _textureName = assets::Texture_Plane;

    _p1 = glm::vec3(position.x - tempW, position.y + tempH, position.z);
    _p2 = glm::vec3(position.x + tempW, position.y + tempH, position.z);
    _p3 = glm::vec3(position.x + tempW, position.y - tempH, position.z);
    _p4 = glm::vec3(position.x - tempW, position.y - tempH, position.z);
    _shader = Shader::GetShader(SHADER_BASE);
    _model = glm::mat4(1.0f);
}


Rectangle::Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4) : GraphicObject(),  
_p1(p1), _p2(p2), _p3(p3), _p4(p4),
_computed(false), _VAO(0), _VBO(0), _texture(0), _vertices(nullptr)
{
    _textureName = assets::Texture_Plane;
    _shader = Shader::GetShader(SHADER_BASE);
    _model = glm::mat4(1.0f);
}

Rectangle::~Rectangle()
{
}

void Rectangle::SetTextureID(assets::Texture textureName)
{
    _textureName = textureName;
}

void Rectangle::SetShader(Shader* shader)
{
    _shader = shader;   
}

void Rectangle::Compute()
{
  if(_computed) return;
  if(_vertices) delete[] _vertices;
  if(_VAO) glDeleteVertexArrays(1, &_VAO);
  if(_VBO) glDeleteBuffers(1, &_VBO);
  

    // 1 2 3 - 1 3 4
    _vertices = new float[30] {
        _p1.x, _p1.y, _p1.z,  0.0f, 0.0f,
        _p2.x, _p2.y, _p2.z,  4.0f, 0.0f,
        _p3.x, _p3.y, _p3.z,  4.0f, 4.0f,
        _p1.x, _p1.y, _p1.z,  0.0f, 0.0f,
        _p3.x, _p3.y, _p3.z,  4.0f, 4.0f,
        _p4.x, _p4.y, _p4.z,  0.0f, 4.0f,
    };
    
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*30, _vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    _shader->Use();
    _shader->SetInt("texture1", 0);

    _computed = true;
}

void Rectangle::Render()
{   
    _shader->Use();
    glBindVertexArray(_VAO);
    glActiveTexture(GL_TEXTURE0);
    if(_textureName != assets::Texture::Texture_None)
        Assets::Bind(_textureName, 0);

    _shader->SetMat4("model", _model);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
