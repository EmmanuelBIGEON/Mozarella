#pragma once

#include <glm/ext.hpp>

#include "GraphicObject.h"
#include "Assets.h"


class Rectangle : public GraphicObject 
{
    public: 

        Rectangle(glm::vec3 position = { 0.0f, 0.0f, 0.0f}, float width = 2.0f, float height = 2.0f); 
        Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4);
        virtual ~Rectangle();
        
        void SetTextureID(assets::Texture textureName);

        virtual void Compute() override;
        virtual void Render() override;

    private:
        glm::mat4 _model;
        glm::vec3 _p1, _p2, _p3, _p4;
        
        assets::Texture _textureName;
        
        bool _computed;
        
        unsigned int _VAO, _VBO;
        float* _vertices;
        unsigned _texture;

};