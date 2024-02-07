#pragma once

#include "Scene.h"
#include "Simple3DView.h"

class SceneSphere : public Scene 
{
    public: 
        SceneSphere();
        virtual ~SceneSphere();

        virtual void Process(Event& event) override;
        virtual void Render() override;
    
    private:
        Simple3DView* _myView;
};