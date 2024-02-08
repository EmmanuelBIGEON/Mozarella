#pragma once 

#include "GraphicObject.h"

#include <glm/ext.hpp>
#include "ColourGroup.h"


class Cube : public GraphicObject 
{
    public: 
        Cube(const glm::vec3& position, const glm::vec3& color);
        Cube(const glm::vec3& position, float width, const glm::vec3& color);
        virtual ~Cube();

        void Assign(ColourGroup* colourGroup);

        virtual void Compute() override;
        virtual void Render() override;

    protected: 
        glm::vec3 _position;
        glm::vec3 _color;
        ColourGroup* _colourGroup;
        
        glm::mat4 _model;
        float _width;

        bool _computed;
        unsigned int _VAO, _VBO;
        float* _vertices;
};