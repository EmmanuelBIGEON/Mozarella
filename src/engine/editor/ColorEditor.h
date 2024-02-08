#pragma once 

#include "Editor.h"
#include "ColourGroup.h"

class ColorEditor : public Editor 
{
    public: 
        ColorEditor(ColourGroup* colorGroup);
        virtual ~ColorEditor();

        void Display() override;

    protected: 
        ColourGroup* _colorGroup;
        bool _open;


};