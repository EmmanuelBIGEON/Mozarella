#pragma once 

class GraphicObject 
{
    public:
        GraphicObject();
        virtual ~GraphicObject();

        virtual void Compute();
        virtual void Render();
};