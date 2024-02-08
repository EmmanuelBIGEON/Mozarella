#include "ColorEditor.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


ColorEditor::ColorEditor(ColourGroup* colorGroup) : Editor(), _colorGroup(colorGroup), _open(true)
{
}

ColorEditor::~ColorEditor()
{
}

void ColorEditor::Display()
{
    ImGuiWindowFlags window_flags = 0;

    if (!ImGui::Begin("ColorEditor", &_open, window_flags))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }

    ImGui::Text("Color widget with Float Display:");
    ImGui::ColorEdit4("Cubes color ##2f", (float*)&_colorGroup->Color(), ImGuiColorEditFlags_Float);
    ImGui::End();
}
