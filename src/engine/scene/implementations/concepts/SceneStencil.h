#pragma once
  
#include "Scene.h"
#include "Simple3DView.h"
#include "ColorEditor.h"

class TexturedCube;

class SceneStencil : public Scene 
{
    public: 
        SceneStencil();
        virtual ~SceneStencil();

        virtual void Process(Event& event) override;
        virtual void Render() override;

    private:
        Simple3DView* _myView;
        TexturedCube* _cube;
        ColorEditor *_editor;
        
        glm::vec3 _color;
};
