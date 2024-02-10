#pragma once 

#include <glm/ext.hpp>

#include "GraphicObject.h"
#include "ColourGroup.h"

class ColoredCube : public GraphicObject 
{
    public: 
        ColoredCube(const glm::vec3& position, const glm::vec3& color);
        ColoredCube(const glm::vec3& position, float width, const glm::vec3& color);
        virtual ~ColoredCube(); 

        void SetWidth(float width);

        void Assign(ColourGroup* colourGroup);

        virtual void Compute() override;
        virtual void Render() override;

    private:
        glm::vec3 _color;
        ColourGroup* _colourGroup;
        
        glm::mat4 _model;
        float _width;

        bool _computed;
        unsigned int _VAO, _VBO;
        float* _vertices;
};

