#pragma once 

#include <map>
#include <string>
#include <glm/vec3.hpp>

#include "Editor.h"
#include "ColourGroup.h"

class ColorEditor : public Editor 
{
    public: 
        ColorEditor();
        virtual ~ColorEditor();

        void Add(const std::string& name, ColourGroup* colorGroup);
        void Add(const std::string& name, float* color);
        void Add(const std::string& name, glm::vec3& color);

        void Display() override;

    protected: 
        std::map<std::string, float*> _colors;
        bool _open;


};