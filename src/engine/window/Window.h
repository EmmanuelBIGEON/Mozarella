#pragma once

#include <memory>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "MozSignal.h"
#include "Event.h"
#include "Scene.h"


class Window
{
    public:
        Window(const std::string& windowName, unsigned int width, unsigned int height);
        virtual ~Window();
        static Window* Create(unsigned int width, unsigned int height);

        void ProcessInputs();
        bool Render();
        void UpdateDataSize(unsigned int width, unsigned int height);
        void GetSize(unsigned int* width, unsigned int* height);
        void SetScene(Scene* pScene);

        void SetCursorMode(bool mode);

        void DisplayEditor(bool mode);
        void ToggleEditor();

        Signal<Event&> OnEvent;

        static Window* activeWindow;
        
        // useful for the camera.
        float frameDeltaTime;

    private: 
        unsigned int _width, _height;
        GLFWwindow* _window;
        Scene* _currentScene;
        bool _editor;
        
};