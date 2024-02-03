#pragma once
  
#include "Scene.h"

class Cube;

class SceneCube : public Scene 
{
    public: 
        SceneCube();
        virtual ~SceneCube();

        virtual void Process(Event& event) override;
        virtual void Render() override;

    private:
        Cube* _cube;

};
