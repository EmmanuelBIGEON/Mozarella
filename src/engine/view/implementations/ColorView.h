#pragma once

#include "View.h"
#include <glm/ext.hpp>

class ColorView : public View 
{
    public:
        ColorView(const glm::vec3& pColor);
        virtual ~ColorView();

        virtual bool Render() override;

    private:
        glm::vec3 _color;

};