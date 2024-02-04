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

    _p1 = glm::vec3(position.x - tempW, position.y + tempH, position.z);
    _p2 = glm::vec3(position.x + tempW, position.y + tempH, position.z);
    _p3 = glm::vec3(position.x + tempW, position.y - tempH, position.z);
    _p4 = glm::vec3(position.x - tempW, position.y - tempH, position.z);
}

Rectangle::~Rectangle()
{
}

void Rectangle::Compute()
{
  if(_computed) return;
  if(_vertices) delete[] _vertices;
  if(_VAO) glDeleteVertexArrays(1, &_VAO);
  if(_VBO) glDeleteBuffers(1, &_VBO);
  
    _model = glm::mat4(1.0f);

    // 1 2 3 - 1 3 4
    _vertices = new float[30] {
        _p1.x, _p1.y, _p1.z,  0.0f, 0.0f,
        _p2.x, _p2.y, _p2.z,  1.0f, 0.0f,
        _p3.x, _p3.y, _p3.z,  1.0f, 1.0f,
        _p1.x, _p1.y, _p1.z,  0.0f, 0.0f,
        _p3.x, _p3.y, _p3.z,  1.0f, 1.0f,
        _p4.x, _p4.y, _p4.z,  0.0f, 1.0f,
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

    // load and create a texture 
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false);
    unsigned char *data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    auto shader = Shader::GetShader(SHADER_BASE);
    shader->Use();
    shader->SetInt("texture1", 0);

    _computed = true;
}

void Rectangle::Render()
{
    auto shader = Shader::GetShader(SHADER_BASE);
    shader->Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glBindVertexArray(_VAO);
    shader->SetMat4("model", _model);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
