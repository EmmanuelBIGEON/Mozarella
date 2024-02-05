#include "QuickEditor.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

QuickEditorPreset QuickEditor::_activePreset = QuickEditorPreset::QuickEditor_None;

void QuickEditor::Display()
{
    switch(_activePreset)
    {
        case QuickEditor_Default:
        {
            ImGui::ShowDemoWindow();
            break;
        }
        case QuickEditor_Demo:
        {
            ImGui::ShowDemoWindow();
            break;
        }
        default: break;
    }
}

void QuickEditor::SetActivePreset(QuickEditorPreset preset)
{
    _activePreset = preset;
}
