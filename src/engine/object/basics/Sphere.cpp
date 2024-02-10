#include "Sphere.h"

#include "MozMath.h" 
#include "Shader.h"

#include <glad/glad.h>

Sphere::Sphere(const glm::vec3& position, unsigned int subdivisionCount) : GraphicObject(position), _computed(false),
 _VAO(0), _VBO(0), _EBO(0), _wireframe(false), _subdivisionCount(subdivisionCount)
{            
}

Sphere::~Sphere()
{
}

void Sphere::SetWireFrameMode()
{
    _wireframe = true;
}

void Sphere::Compute()
{
    if(_computed) return; 
    mozmath::CalculateSphere(_vertices, _subdivisionCount);

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*_vertices.size(), _vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    _computed = true;
}

void Sphere::Render()
{
    auto shader = Shader::GetShader(SHADER_SPHERE_TEST);
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, _position);
    shader->SetMat4("model", model);
    shader->Use();
    glBindVertexArray(_VAO);

    if(_wireframe)
    {
        glLineWidth(1.0f);
        glDrawArrays(GL_LINES, 0, _vertices.size() / 3);
    }else 
    {
        glDrawArrays(GL_TRIANGLES, 0, _vertices.size() / 3);
    }
}
