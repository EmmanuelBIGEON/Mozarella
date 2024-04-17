#pragma once
  
#include "Scene.h"
#include "Simple3DView.h"
#include "GraphicContext.h"

class TexturedCube;

class SceneFramebuffer : public Scene 
{
    public: 
        SceneFramebuffer();
        virtual ~SceneFramebuffer();

        virtual void Process(Event& event) override;
        virtual void Render() override;
        
        void SetupFramebuffer();
        void renderFrameBuffer();

    private:
        Simple3DView* _myView;
        TexturedCube* _cube;

        unsigned int _framebuffer;
        unsigned int _VAOf, _VBOf, _rbo;

        unsigned int _textureColorbuffer;
        float* _verticesf;
};
