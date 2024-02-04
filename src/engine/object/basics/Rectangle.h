#pragma once

#include <glm/ext.hpp>

#include "GraphicObject.h"

class Rectangle : public GraphicObject 
{
    public: 

        Rectangle(glm::vec3 position = { 0.0f, 0.0f, 0.0f}, float width = 2.0f, float height = 2.0f); 
        virtual ~Rectangle();
        
        virtual void Compute() override;
        virtual void Render() override;

    private:
        glm::mat4 _model;
        glm::vec3 _p1, _p2, _p3, _p4;
        
        bool _computed;
        
        unsigned int _VAO, _VBO;
        float* _vertices;
        unsigned _texture;

};