#pragma once 

#include <vector>
#include <glm/ext.hpp>

#include "GraphicObject.h"

class Sphere : public GraphicObject 
{
    public:
        Sphere(const glm::vec3& position, unsigned int subdivisionCount = 2);
        virtual ~Sphere();

        void SetWireFrameMode();

        virtual void Compute() override;
        virtual void Render() override;
    private: 
    
        glm::vec3 _position;
        unsigned int _VAO, _VBO, _EBO;
        std::vector<float> _vertices;
        bool _computed;
        bool _wireframe;
        unsigned int _subdivisionCount;
        
};