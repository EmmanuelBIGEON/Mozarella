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

        void AddObject(GraphicObject* pObject, bool hasTransparency = false);
        void RemoveObject(GraphicObject* pObject);
        
        // Call this method when you have transparency issues.
        // Display : Opaques elements first, then transparent elements by distance. (far first)
        void Sort(const glm::vec3& cameraPosition);

        void Render();
        

    private: 

        std::vector<GraphicObject*> _objects;

        std::vector<GraphicObject*> _opaquesObjects;
        std::vector<GraphicObject*> _transparencyObjects;
};