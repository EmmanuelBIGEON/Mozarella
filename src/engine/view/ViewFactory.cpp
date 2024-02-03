#include "ViewFactory.h"


View* ViewFactory::CreateDefaultView()
{
    auto view = new View();
    return view;
}

ColorView* ViewFactory::CreateColorView(const glm::vec3& pColor)
{
    auto view = new ColorView(pColor);
    return view;
}

Simple3DView* ViewFactory::CreateSimple3DView()
{
    auto view = new Simple3DView();
    return view;
}