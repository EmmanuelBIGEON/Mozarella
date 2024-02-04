cmake_minimum_required(VERSION 3.18)

include_directories(
    src/engine
    src/engine/assets
    src/engine/common
    src/engine/context
    src/engine/event
    src/engine/object
    src/engine/object/basics
    src/engine/scene
    src/engine/scene/implementations
    src/engine/shader
    src/engine/texture
    src/engine/view
    src/engine/view/implementations
    src/engine/window
    
    src/engine/imgui

    include
)

set(SRCS
    src/main.cpp
    src/glad.c

    src/engine/assets/Assets.cpp

    src/engine/Engine.cpp

    src/engine/scene/Scene.cpp
    src/engine/scene/SceneFactory.cpp
    src/engine/scene/implementations/SceneColor.cpp 
    src/engine/scene/implementations/SceneCube.cpp 
    src/engine/scene/implementations/SceneCamera.cpp 

    src/engine/view/View.cpp 
    src/engine/view/Camera.cpp 
    src/engine/view/ViewFactory.cpp
    src/engine/view/implementations/ColorView.cpp
    src/engine/view/implementations/Simple3DView.cpp
    
    src/engine/window/Window.cpp
    
    src/engine/context/GraphicContext.cpp 
    
    src/engine/shader/Shader.cpp
    
    src/engine/texture/Texture.cpp

    src/engine/object/GraphicObject.cpp 
    src/engine/object/ObjectFactory.cpp 
    src/engine/object/basics/Cube.cpp 
    src/engine/object/basics/Rectangle.cpp 
)

set(SRCS_IMGUI
    src/engine/imgui/imgui.cpp
    src/engine/imgui/imgui_draw.cpp
    src/engine/imgui/imgui_demo.cpp
    src/engine/imgui/imgui_tables.cpp
    src/engine/imgui/imgui_widgets.cpp

    src/engine/imgui/imgui_impl_glfw.cpp
    src/engine/imgui/imgui_impl_opengl3.cpp # 3 ? 
)

project(Mozarella)

add_executable(Mozarella ${SRCS} ${SRCS_IMGUI})
target_compile_features(Mozarella PRIVATE cxx_std_17)

target_link_libraries(Mozarella
    ${GLFW_DIR}/glfw3.lib
    ${FREETYPE_DIR}/lib/freetyped.lib
)

install(TARGETS Mozarella DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY shaders DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY textures DESTINATION ${CMAKE_INSTALL_PREFIX})