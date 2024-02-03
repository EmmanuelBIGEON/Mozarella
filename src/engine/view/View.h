#pragma once

#include "Event.h"

class View
{
    public:
        View();
        virtual ~View();

        virtual bool Render();

    private:
};