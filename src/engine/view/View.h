#pragma once

class View
{
    public:
        View();
        virtual ~View();

        virtual bool Render();
};