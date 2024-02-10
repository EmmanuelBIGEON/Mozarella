#pragma once

#include <glm/ext.hpp>

#include "GraphicObject.h"
#include "Assets.h"

class TexturedCube : public GraphicObject 
{
    public: 
        TexturedCube(const glm::vec3& position);
        virtual ~TexturedCube(); 

        void ToggleRotation();
        void SetTextureID(assets::Texture textureName);

        void ApplyScale(float scale);

        void EnableStencilMode();

        virtual void Compute() override;
        virtual void Render() override;

    private:
        glm::mat4 _model;

        assets::Texture _textureName;

        bool _computed;
        bool _rotating;
        bool _stencilMode;

        float _scale;

        unsigned int _VAO, _VBO;
        float* _vertices;
        unsigned _texture;
};

