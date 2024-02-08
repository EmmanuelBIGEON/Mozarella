#pragma once 

#include "GraphicObject.h"
#include <glm/ext.hpp>

class LightSource : public GraphicObject
{
    public:
        LightSource(const glm::vec3& position, const glm::vec3& color);
        virtual ~LightSource();

        void SetWidth(float width);

        glm::vec3& Color();
        glm::vec3& Position();

        virtual void Compute() override;
        virtual void Render() override;

    private:
        glm::mat4 _model;
        glm::vec3 _position;
        glm::vec3 _color;
        float _width;

        bool _computed;
        unsigned int _VAO, _VBO;
        float* _vertices;
};