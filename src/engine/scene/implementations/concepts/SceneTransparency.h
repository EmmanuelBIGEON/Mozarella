#pragma once
  
#include "Scene.h"
#include "Simple3DView.h"
#include "ColourGroup.h"
#include "GraphicContext.h"

#include <memory> 

class SceneTransparency : public Scene 
{
    public: 
        SceneTransparency();
        virtual ~SceneTransparency();

        virtual void Process(Event& event) override;
        virtual void Render() override;

    private:
        Simple3DView* _myView;
        std::shared_ptr<GraphicContext> _myContext;
        
        ColourGroup *_groupColor;
};
