#include "Simple3DView.h"

#include <glad/glad.h>

#include "GraphicContext.h"

#include "Window.h"
#include "Shader.h"

Simple3DView::Simple3DView() : _context(nullptr)
{
    _view          = glm::mat4(1.0f);
    _projection    = glm::mat4(1.0f);

    unsigned int screenWidth, screenHeight;
    Window::activeWindow->GetSize(&screenWidth, &screenHeight);
    _projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
    _view       = glm::translate(_view, glm::vec3(0.0f, 0.0f, -3.0f));
}

Simple3DView::~Simple3DView()
{
}

bool Simple3DView::Render()
{
    glClearColor(0.7f, 0.7f, 0.7f , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    // ugly
    auto shader = Shader::GetShader(SHADER_CUBE);
    if(!shader) return false;
    
    shader->Use();
    shader->SetMat4("projection", _projection);
    shader->SetMat4("view", _view);
    
    _context->Render();

    return true;
}

void Simple3DView::SetContext(const std::shared_ptr<GraphicContext>& pContext)
{
    _context = pContext;
}

std::shared_ptr<GraphicContext> Simple3DView::GetContext()
{
    return _context;
}