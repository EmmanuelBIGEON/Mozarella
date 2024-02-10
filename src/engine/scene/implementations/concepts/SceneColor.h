#pragma once

#include <glm/ext.hpp>

#include "Scene.h"

class SceneColor : public Scene
{
    public:
        SceneColor(const glm::vec3& pColor);
        virtual ~SceneColor();

        virtual void Render() override;

    private:
        glm::vec3 _color;
};