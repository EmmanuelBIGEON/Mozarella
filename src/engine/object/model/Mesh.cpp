#include "Mesh.h"

#include <glad/glad.h>

#include "Shader.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures) :
 GraphicObject(), _VAO(0), _VBO(0), _EBO(0), _computed(false)
{
    _indices = std::move(indices);
    _vertices = std::move(vertices);
    _textures = std::move(textures);
}

Mesh::~Mesh()
{
}

void Mesh::Compute()
{
    if(_computed) return;

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);
  
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), 
                 &_indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);

    _computed = true;
}

void Mesh::Render()
{
    auto shader = Shader::GetShader(ShaderID::SHADER_MATERIAL);
    shader->Use();
    glBindVertexArray(_VAO);
    for(unsigned int i = 0; i < _textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0); 
        std::string name = _textures[i]->type;
        shader->SetInt(("material." + name).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, _textures[i]->ID);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
