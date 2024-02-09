cmake_minimum_required(VERSION 3.18)

include_directories(
    src/engine
    src/engine/assets
    src/engine/common
    src/engine/common/math 
    src/engine/common/math/algorithm
    src/engine/context
    src/engine/editor
    src/engine/event
    src/engine/object
    src/engine/object/model
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
    src/engine/Engine.cpp
    src/engine/window/Window.cpp

    src/engine/assets/Assets.cpp

    src/engine/common/math/algorithm/MozMathSubdivision.cpp

    src/engine/editor/ColorEditor.cpp
    src/engine/editor/QuickEditor.cpp

    src/engine/scene/Scene.cpp
    src/engine/scene/SceneFactory.cpp
    src/engine/scene/implementations/SceneColor.cpp 
    src/engine/scene/implementations/SceneCube.cpp 
    src/engine/scene/implementations/SceneCamera.cpp 
    src/engine/scene/implementations/SceneMesh.cpp 
    src/engine/scene/implementations/SceneLight.cpp 
    src/engine/scene/implementations/SceneSphere.cpp 
    src/engine/scene/implementations/SceneEdit.cpp 

    src/engine/view/View.cpp 
    src/engine/view/Camera.cpp 
    src/engine/view/ViewFactory.cpp
    src/engine/view/implementations/ColorView.cpp
    src/engine/view/implementations/Simple3DView.cpp
    
    
    src/engine/context/GraphicContext.cpp 
    
    src/engine/shader/Shader.cpp
    
    src/engine/texture/Texture.cpp
    src/engine/texture/TextureLoader.cpp

    src/engine/object/GraphicObject.cpp 
    src/engine/object/ObjectFactory.cpp 
    src/engine/object/model/Mesh.cpp 
    src/engine/object/model/Model.cpp 
    src/engine/object/model/ModelLoader.cpp 
    src/engine/object/basics/LightSource.cpp 
    src/engine/object/basics/Cube.cpp 
    src/engine/object/basics/ColoredCube.cpp 
    src/engine/object/basics/TexturedCube.cpp 
    src/engine/object/basics/Rectangle.cpp 
    src/engine/object/basics/Sphere.cpp 
)

set(SRCS_IMGUI
    src/engine/imgui/imgui.cpp
    src/engine/imgui/imgui_draw.cpp
    src/engine/imgui/imgui_demo.cpp
    src/engine/imgui/imgui_tables.cpp
    src/engine/imgui/imgui_widgets.cpp

    src/engine/imgui/imgui_impl_glfw.cpp
    src/engine/imgui/imgui_impl_opengl3.cpp 
)

project(Mozarella)

add_executable(Mozarella ${SRCS} ${SRCS_IMGUI})
target_compile_features(Mozarella PRIVATE cxx_std_17)

target_link_libraries(Mozarella
    ${GLFW_DIR}/glfw3.lib
    ${FREETYPE_DIR}/lib/freetyped.lib
    ${ASSIMP_DIR}/assimp-vc143-mt.lib
    ${ASSIMP_DIR}/zlibstatic.lib
)

install(TARGETS Mozarella DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY shaders DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY textures DESTINATION ${CMAKE_INSTALL_PREFIX})