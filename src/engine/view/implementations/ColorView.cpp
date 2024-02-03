#include "ColorView.h"

#include <glad/glad.h>

ColorView::ColorView(const glm::vec3& pColor) : _color(pColor)
{
}

ColorView::~ColorView()
{
}

bool ColorView::Render()
{
    glClearColor(_color.r, _color.g, _color.b , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    return true;
}
