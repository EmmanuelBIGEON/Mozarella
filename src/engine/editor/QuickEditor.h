#pragma once


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

enum QuickEditorPreset
{
    QuickEditor_None,
    QuickEditor_Demo,
    QuickEditor_Default,
};

class QuickEditor
{
    public: 
        static void Display();
        static void SetActivePreset(QuickEditorPreset preset);

    private:
        static QuickEditorPreset _activePreset;
};