#pragma once

#include "Scene.h"
#include "Simple3DView.h"

class SceneMesh : public Scene 
{
    public: 
        SceneMesh();
        virtual ~SceneMesh();

        virtual void Process(Event& event) override;
        virtual void Render() override;
    
    private:
        Simple3DView* _myView;
};