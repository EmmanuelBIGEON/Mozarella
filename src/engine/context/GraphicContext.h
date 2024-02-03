#pragma once 

#include <vector>

#include "GraphicObject.h"

//! Contains graphics objects, allowing us to share it between multiple views
//! instead of having the object directly into the views 
class GraphicContext
{
    public: 
        GraphicContext();
        virtual ~GraphicContext();

        void AddObject(GraphicObject* pObject);
        void RemoveObject(GraphicObject* pObject);
        void Render();
        

    private: 

        std::vector<GraphicObject*> _objects;
};