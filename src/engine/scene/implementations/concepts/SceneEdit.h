#pragma once 

#include "Scene.h"
#include "ColourGroup.h"
#include "ColorEditor.h"
#include "Simple3DView.h"

class SceneEdit : public Scene 
{
    public: 
        SceneEdit();
        void NewFunction();
        virtual ~SceneEdit();

        virtual void Process(Event &event) override;
        virtual void Render() override;

    private:
        Simple3DView *_myView;
        ColourGroup *_groupColor;
        ColorEditor *_editor;

        glm::vec3 _lightColor;
};