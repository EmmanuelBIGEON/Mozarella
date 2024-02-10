#pragma once 

#include <glm/vec3.hpp>

class GraphicObject 
{
    public:
        GraphicObject(const glm::vec3& position = { 0.0f, 0.0f, 0.0f});
        virtual ~GraphicObject();

        void SetPosition(const glm::vec3& position);
        const glm::vec3& GetPosition();

        glm::vec3& Position();

        virtual void Compute();
        virtual void Render();

    protected:
        glm::vec3 _position;
};