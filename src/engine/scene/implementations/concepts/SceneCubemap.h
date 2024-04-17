#pragma once 

#include "Scene.h"
#include "Simple3DView.h"

class SceneCubemap : public Scene 
{
    public: 
        SceneCubemap();
        virtual ~SceneCubemap();

        virtual void Process(Event& event) override;
        virtual void Render() override;

        void InitSkybox();
        void DrawSkybox();
    
    private:
        Simple3DView* _myView;

        Texture* _skyboxTexture;
        unsigned int _VAO, _VBO;
        float* _vertices;
};