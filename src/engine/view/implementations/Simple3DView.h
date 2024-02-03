#pragma once 

#include <memory>
#include <glm/ext.hpp>


#include "View.h"

class GraphicContext;

class Simple3DView : public View
{
    public: 
        Simple3DView();
        virtual ~Simple3DView();

        virtual bool Render() override;

        void SetContext(const std::shared_ptr<GraphicContext>& pContext);
        std::shared_ptr<GraphicContext> GetContext();

    private:
        std::shared_ptr<GraphicContext> _context;

        glm::mat4 _view;
        glm::mat4 _projection;
};