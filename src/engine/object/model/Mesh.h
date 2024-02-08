#pragma once

#include <vector>
#include <glm/ext.hpp>

#include "Texture.h"
#include "GraphicObject.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh : public GraphicObject
{
    public:
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