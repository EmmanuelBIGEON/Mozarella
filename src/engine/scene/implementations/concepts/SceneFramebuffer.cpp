#include "SceneFramebuffer.h"

#include <memory>

#include "ViewFactory.h"
#include "ObjectFactory.h"
#include "GraphicContext.h"

#include <glad/glad.h>
#include <iostream>


SceneFramebuffer::SceneFramebuffer() : _framebuffer(0), _VAOf(0), _VBOf(0), _verticesf(nullptr),
 _rbo(0), _textureColorbuffer(0)
{
    _myView = ViewFactory::CreateSimple3DView();
    auto context = std::make_shared<GraphicContext>();
    _cube = ObjectFactory::CreateTexturedCube({0.0f, 0.0f, 0.0f});
    _cube->SetTextureID(assets::Texture::Texture_Cube2);
    _cube->ToggleRotation();
    context->AddObject(_cube);


    // Add a plane.
    glm::vec3 p1 = glm::vec3(10.0f, -1.0f, 10.0f);
    glm::vec3 p2 = glm::vec3(-10.0f, -1.0f, 10.0f);
    glm::vec3 p3 = glm::vec3(-10.0f, -1.0f, -10.0f);
    glm::vec3 p4 = glm::vec3(10.0f, -1.0f, -10.0f);
    auto plane = ObjectFactory::CreateRectangle(p1, p2,  p3, p4);
    context->AddObject(plane);

    // Add a camera to the scene.
    _myView->EnableCamera();

    SetupFramebuffer();


    _myView->SetContext(context);
    Add(_myView);
}

SceneFramebuffer::~SceneFramebuffer()
{
    if(_verticesf) delete _verticesf;
}

void SceneFramebuffer::Render()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    glEnable(GL_DEPTH_TEST);
    

    for(const auto& view : _views)
    {
        if(!view->Render())
        {
            _views.erase(std::remove(_views.begin(), _views.end(), view), _views.end());
            break;
        }
    }

    renderFrameBuffer();
}

void SceneFramebuffer::Process(Event& event)
{
    _myView->UpdateCamera(event);

    if(event.GetEventType() == EventType::EVENT_KEY)
    {
        KeyEvent* keyEvent = (KeyEvent*)&event;
        if(keyEvent->GetKeyType() == EventKeyType::EVENT_KEY_PRESSED)
        {
            KeyPressedEvent* keyPressedEvent = (KeyPressedEvent*)&event;

            if(keyPressedEvent->key == Key_U)
            {
                _cube->ToggleRotation();
            }
        }
    }
}


void SceneFramebuffer::SetupFramebuffer()
{

    _verticesf = new float[24] { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    auto screenShader = Shader::GetShader(SHADER_SCREEN);
    screenShader->Use();
    screenShader->SetInt("screenTexture", 0);

    glGenVertexArrays(1, &_VAOf);
    glGenBuffers(1, &_VBOf);
    glBindVertexArray(_VAOf);
    glBindBuffer(GL_ARRAY_BUFFER, _VBOf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, _verticesf, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));


    // framebuffer configuration
    // -------------------------

    unsigned int scrWidth, screenHeight;
    Window::activeWindow->GetSize(&scrWidth, &screenHeight);

    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

    // create a color attachment texture
    glGenTextures(1, &_textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, _textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scrWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureColorbuffer, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, _rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scrWidth, screenHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void SceneFramebuffer::renderFrameBuffer()
{
        // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
        glClear(GL_COLOR_BUFFER_BIT);

        auto screenShader = Shader::GetShader(SHADER_SCREEN);
        screenShader->Use();
        glBindVertexArray(_VAOf);
        glBindTexture(GL_TEXTURE_2D, _textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
        glActiveTexture(GL_TEXTURE0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
}
