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
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
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