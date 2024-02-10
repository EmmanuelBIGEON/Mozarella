#include "Window.h"

#include <iostream>
#include <set>

#include "Shader.h"
#include "QuickEditor.h"
#include "Assets.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Window* Window::activeWindow = nullptr;

void HeldDownKey_Handling();

bool keyhelddown = false;
double timeBetweenKeyPress = 0;
double timeBetweenKeyPressMax = 0.001;
int rememberedKey = 0;
bool longpress = true;
double timeBetweenKeyPressMaxLong = 0.005;
double lastMouseX = 0, lastMouseY = 0;
std::set<int> holdedKeys = {};
float lastFrame = 0.0f;

Window::Window(const std::string& windowName, unsigned int width, unsigned int height) : _height(height), _width(width), frameDeltaTime(0)
{
    Window::activeWindow = this;
    // Specify OpenGL version and other things needed before creating the window.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // We create the window.
    _window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
    if (_window == NULL){ std::cout << "Failed glfwCreateWindow" << std::endl; glfwTerminate(); return;}

    // display window at the center of the screen
    int count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);
    const GLFWvidmode* mode = glfwGetVideoMode(monitors[0]);
    glfwSetWindowPos(_window, (mode->width - width) / 2, (mode->height - height) / 2);

    glfwMakeContextCurrent(_window);
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
    glfwSetKeyCallback(_window, key_callback);
    glfwSetCursorPosCallback(_window, mouse_callback);
    glfwSetMouseButtonCallback(_window, mouse_button_callback);
    glfwSetScrollCallback(_window, scroll_callback);
    
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // Initiliaze Glad to use OpenGL functions.
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){ std::cout << "Failed to initialize GLAD" << std::endl; return; }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);  
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    Shader::InitShaders();
    Assets::LoadAssets(AssetType::AssetType_All);
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(_window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

}

Window::~Window()
{
    if(_window) delete _window;
}

Window* Window::Create(unsigned int width, unsigned int height)
{
    return new Window("aze", width, height);
}

bool Window::Render()
{
    if(glfwWindowShouldClose(_window)) return false;
    Window::activeWindow = this;

    glfwPollEvents();
    
    if(_editor)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        QuickEditor::Display();
    }

    float currentFrame = static_cast<float>(glfwGetTime());
    frameDeltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    ProcessInputs();

    
    if(_currentScene) _currentScene->Render();

    if(_editor)
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    glfwSwapBuffers(_window);

    return true;
}

void Window::ProcessInputs()
{
    // Only process keys for now.
    for(const auto& key : holdedKeys)
    {
        KeyRepeatedEvent event(key);
        Window::activeWindow->OnEvent.Emit(event);

    }
}

void Window::DisplayEditor(bool mode)
{
    _editor = mode;
}

void Window::ToggleEditor()
{
    _editor = !_editor;
}

void Window::SetCursorMode(bool mode)
{
    if(mode)
    {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }else 
    {
        glfwSetInputMode(_window, GLFW_CURSOR,  GLFW_CURSOR_NORMAL);
    }
}

void Window::UpdateDataSize(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
}

void Window::GetSize(unsigned int* width, unsigned int* height)
{
    *width = _width;
    *height = _height;
}
void Window::SetScene(Scene* pScene)
{
    _currentScene = pScene;
    _currentScene->Connect(this);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    if(Window::activeWindow) Window::activeWindow->UpdateDataSize(width, height);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
        
    if(action == GLFW_REPEAT)
    {
        KeyPressedEvent event(key);
        Window::activeWindow->OnEvent.Emit(event);
    }
    else if(action == GLFW_PRESS)
    {
        KeyPressedEvent event(key);
        Window::activeWindow->OnEvent.Emit(event);
        timeBetweenKeyPress = glfwGetTime();
        rememberedKey = key;
        holdedKeys.insert(key);
    }else if(action == GLFW_RELEASE)
    {
        KeyReleasedEvent event(key);
        Window::activeWindow->OnEvent.Emit(event);
        holdedKeys.erase(key);
        longpress = false;
    }
}

void HeldDownKey_Handling()
{
    for(const auto& key : holdedKeys)
    {
        if(!longpress && glfwGetTime() - timeBetweenKeyPress > timeBetweenKeyPressMax)
            {
                KeyPressedEvent event(key);
                Window::activeWindow->OnEvent.Emit(event);
                timeBetweenKeyPress = glfwGetTime();
            }
    }
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    MouseMovedEvent event(xpos, ypos);
    Window::activeWindow->OnEvent.Emit(event);

    lastMouseX = xpos;
    lastMouseY = ypos;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        if(button == GLFW_MOUSE_BUTTON_LEFT)
        {
            MousePressedEvent event(lastMouseX, lastMouseY, MouseButton::MOUSE_BUTTON_LEFT);
            Window::activeWindow->OnEvent.Emit(event);
        }else if(button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            MousePressedEvent event(lastMouseX, lastMouseY, MouseButton::MOUSE_BUTTON_RIGHT);
            Window::activeWindow->OnEvent.Emit(event);
        }else if(button == GLFW_MOUSE_BUTTON_MIDDLE)
        {
            MousePressedEvent event(lastMouseX, lastMouseY, MouseButton::MOUSE_BUTTON_MIDDLE);
            Window::activeWindow->OnEvent.Emit(event);
        }
    
    }else if(action == GLFW_RELEASE)
    {
        if(button == GLFW_MOUSE_BUTTON_LEFT)
        {
            MouseReleasedEvent event(lastMouseX, lastMouseY, MouseButton::MOUSE_BUTTON_LEFT);
            Window::activeWindow->OnEvent.Emit(event);
        }else if(button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            MouseReleasedEvent event(lastMouseX, lastMouseY, MouseButton::MOUSE_BUTTON_RIGHT);
            Window::activeWindow->OnEvent.Emit(event);
        }else if(button == GLFW_MOUSE_BUTTON_MIDDLE)
        {
            MouseReleasedEvent event(lastMouseX, lastMouseY, MouseButton::MOUSE_BUTTON_MIDDLE);
            Window::activeWindow->OnEvent.Emit(event);
        }
    }
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    WheelEvent event(xoffset, yoffset);
    Window::activeWindow->OnEvent.Emit(event);
}