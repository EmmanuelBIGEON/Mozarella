#include "Simple3DView.h"

#include <glad/glad.h>

#include "GraphicContext.h"

#include "Window.h"
#include "Shader.h"

Simple3DView::Simple3DView() : _context(nullptr), _cameraActive(false)
{
    _camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    _view          = glm::mat4(1.0f);
    _projection    = glm::mat4(1.0f);

    unsigned int screenWidth, screenHeight;
    Window::activeWindow->GetSize(&screenWidth, &screenHeight);
    _projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
    _view       = glm::translate(_view, glm::vec3(0.0f, 0.0f, -3.0f));
}

Simple3DView::~Simple3DView()
{
    if(_camera) delete _camera;
}

bool Simple3DView::Render()
{
    glClearColor(0.7f, 0.7f, 0.7f , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    
    if (_cameraActive)
    {
        unsigned int screenWidth, screenHeight;
        Window::activeWindow->GetSize(&screenWidth, &screenHeight);
        auto projection = glm::perspective(glm::radians(_camera->Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
        
        Shader::UpdateProjectionMatrix(projection);
        Shader::UpdateViewMatrix(_camera->GetViewMatrix());
    }
    else
    {
        
        Shader::UpdateProjectionMatrix(_projection);
        Shader::UpdateViewMatrix(_view);
    } 

    _context->Render();

    return true;
}

void Simple3DView::EnableCamera()
{
    _cameraActive = true;
}

void Simple3DView::UpdateCamera(Event& event)
{
    if(_cameraActive)
    {
        _camera->Update(event);
    }
}

Camera* Simple3DView::GetCamera()
{
    return _camera;
}


void Simple3DView::SetContext(const std::shared_ptr<GraphicContext>& pContext)
{
    _context = pContext;
}

std::shared_ptr<GraphicContext> Simple3DView::GetContext()
{
    return _context;
}