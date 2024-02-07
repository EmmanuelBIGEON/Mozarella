#pragma once 

#include "Scene.h"
#include "ColourGroup.h"
#include "Simple3DView.h"

class SceneEdit : public Scene 
{
    public: 
        SceneEdit();
        virtual ~SceneEdit();

        virtual void Process(Event& event) override;
        virtual void Render() override;
    
    private:
        Simple3DView* _myView;
        ColourGroup* _groupColor;
};