#pragma once

#include "Scene.h"
#include "ColourGroup.h"
#include "Simple3DView.h"
#include "LightSource.h"
#include "ColorEditor.h"

#include <glm/ext.hpp>


class SceneLight : public Scene 
{
    public: 
        SceneLight();
        virtual ~SceneLight();

        virtual void Process(Event& event) override;
        virtual void Render() override;
    
    private:
        Simple3DView* _myView;
        ColorEditor *_editor;

        ColourGroup *_groupColor;

        LightSource* _lightSource;
};