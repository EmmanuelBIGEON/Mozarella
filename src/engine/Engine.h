#pragma once

#include <unordered_map>


#include "Window.h"

//! \class Engine
//! \brief The mozarella engine
class Engine
{
    public:
        Engine();
        virtual ~Engine();

        void Add(Window *);

        void Init();

        //! Tant qu'il y a une fenetre active, on renvoie true.
        bool Run();

        void Remove(Window* pWindow);
        
    private:
        std::unordered_map<unsigned int, Window*> _mapWindows;

};