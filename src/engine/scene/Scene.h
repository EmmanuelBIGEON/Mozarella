#pragma once

#include <vector>

#include "View.h"

class Window;

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        void Add(View* pView);

        // Connecte la gestion evenementielle
        void Connect(Window* window);

        virtual void Render();

    protected:
        std::vector<View*> _views;
};