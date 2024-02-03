#pragma once 

#include "Scene.h"
#include "Simple3DView.h"

class SceneCamera : public Scene 
{
    public: 
        SceneCamera();
        virtual ~SceneCamera();

        virtual void Process(Event& event) override;
        virtual void Render() override;
    
    private:
        Simple3DView* _myView;
};