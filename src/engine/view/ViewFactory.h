#pragma once

#include <glm/ext.hpp>

#include "View.h"

#include "ColorView.h"
#include "Simple3DView.h"

class ViewFactory
{
    public: 
        static View* CreateDefaultView();
        static ColorView* CreateColorView(const glm::vec3& pColor);
        static Simple3DView* CreateSimple3DView();
};