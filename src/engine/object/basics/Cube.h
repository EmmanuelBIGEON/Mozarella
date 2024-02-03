#pragma once

#include <glm/ext.hpp>

#include "GraphicObject.h"

class Cube : public GraphicObject 
{
    public: 
        Cube(const glm::vec3& position);
        virtual ~Cube(); 

        void ToggleRotation();

        virtual void Compute() override;
        virtual void Render() override;

    private:
        glm::vec3 _position;
        glm::mat4 _model;

        bool _computed;
        bool _rotating;

        unsigned int _VAO, _VBO;
        float* _vertices;
        unsigned _texture;
};

