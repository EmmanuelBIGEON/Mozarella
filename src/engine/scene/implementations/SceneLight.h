#pragma once

#include "Scene.h"
#include "Simple3DView.h"

class SceneLight : public Scene 
{
    public: 
        SceneLight();
        virtual ~SceneLight();

        virtual void Process(Event& event) override;
        virtual void Render() override;
    
    private:
        Simple3DView* _myView;
};