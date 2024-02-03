#pragma once
  
#include "Scene.h"

class SceneCube : public Scene 
{
    public: 
        SceneCube();
        virtual ~SceneCube();

        virtual void Render() override;
};
