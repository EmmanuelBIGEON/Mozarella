#pragma once
  
#include "Scene.h"

class TexturedCube;

class SceneCube : public Scene 
{
    public: 
        SceneCube();
        virtual ~SceneCube();

        virtual void Process(Event& event) override;
        virtual void Render() override;

    private:
        TexturedCube* _cube;

};
