#pragma once

#include <vector>

#include "View.h"
#include "MozSignal.h"

class Window;

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        void Add(View* pView);

        // Connecte la gestion evenementielle
        void Connect(Window* window);

        virtual void Process(Event& event);
        virtual void Render();

    protected:
        View* _activeView;
        std::vector<View*> _views;

        Slot<Event&>* _slot;
};