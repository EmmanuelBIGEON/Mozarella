#include "ColorEditor.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


ColorEditor::ColorEditor() : Editor(), _open(true)
{
}

ColorEditor::~ColorEditor()
{
}

void ColorEditor::Add(const std::string& name, ColourGroup* colorGroup)
{
    _colors[name] = (float*)&colorGroup->Color();
}

void ColorEditor::Add(const std::string& name, float* color)
{
    _colors[name] = color;
}

void ColorEditor::Add(const std::string& name, glm::vec3& color)
{
    _colors[name] = (float*)&color;
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

    for(const auto& pair : _colors)
    {
        std::string label = pair.first + "##2f";
        ImGui::ColorEdit3(label.c_str(), pair.second, ImGuiColorEditFlags_Float);
    }
    ImGui::End();
}
