#pragma once

#include <vector>
#include <glm/ext.hpp>

#include "GraphicObject.h"

#include "Texture.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh : public GraphicObject
{
    public:
        Mesh(); // inutile pour le moment.
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures);
        virtual ~Mesh();
        
        virtual void Compute() override;
        virtual void Render() override;
    private:
        std::vector<Vertex>        _vertices;
        std::vector<unsigned int>  _indices;
        std::vector<Texture*>      _textures;
    
        unsigned int _VAO, _VBO, _EBO;

        bool _computed;

};  