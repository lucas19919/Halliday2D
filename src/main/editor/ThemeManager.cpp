#include "main/editor/ThemeManager.h"
#include "external/imgui/imgui.h"

namespace Editor {

void ThemeManager::ApplyTheme(EditorTheme theme) {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    ImGui::StyleColorsDark();
    style.WindowRounding = 4.0f;
    style.FrameRounding = 3.0f;
    style.GrabRounding = 3.0f;
    style.TabRounding = 4.0f;
    style.ScrollbarRounding = 9.0f;
    style.FrameBorderSize = 0.0f;

    switch (theme) {
        case EditorTheme::Light: 
            ImGui::StyleColorsLight();
            colors[ImGuiCol_WindowBg]               = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
            colors[ImGuiCol_ChildBg]                = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
            colors[ImGuiCol_PopupBg]                = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
            colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.10f);
            colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_FrameBg]                = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
            colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
            colors[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
            colors[ImGuiCol_TitleBg]                = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
            colors[ImGuiCol_TitleBgActive]          = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
            colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
            colors[ImGuiCol_MenuBarBg]              = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
            colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
            colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
            colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
            colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
            colors[ImGuiCol_CheckMark]              = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_SliderGrab]             = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
            colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_Button]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
            colors[ImGuiCol_ButtonHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_ButtonActive]           = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
            colors[ImGuiCol_Header]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
            colors[ImGuiCol_HeaderHovered]          = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
            colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_Separator]              = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
            colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
            colors[ImGuiCol_SeparatorActive]        = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
            colors[ImGuiCol_ResizeGrip]             = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
            colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
            colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
            colors[ImGuiCol_Tab]                    = ImVec4(0.76f, 0.80f, 0.84f, 0.93f);
            colors[ImGuiCol_TabHovered]             = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
            colors[ImGuiCol_TabActive]              = ImVec4(0.60f, 0.73f, 0.88f, 1.00f);
            colors[ImGuiCol_TabUnfocused]           = ImVec4(0.92f, 0.93f, 0.94f, 0.99f);
            colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.74f, 0.82f, 0.91f, 1.00f);
            colors[ImGuiCol_DockingPreview]         = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
            colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
            colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
            colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            style.WindowRounding = 6.0f;
            style.FrameRounding = 4.0f;
            break;

        case EditorTheme::Retro:
            colors[ImGuiCol_Text]                   = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
            colors[ImGuiCol_TextDisabled]           = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
            colors[ImGuiCol_WindowBg]               = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
            colors[ImGuiCol_ChildBg]                = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
            colors[ImGuiCol_PopupBg]                = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
            colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.30f); 
            colors[ImGuiCol_BorderShadow]           = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
            colors[ImGuiCol_FrameBg]                = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
            colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.90f, 0.90f, 0.95f, 1.00f);
            colors[ImGuiCol_FrameBgActive]          = ImVec4(0.80f, 0.80f, 0.90f, 1.00f);
            colors[ImGuiCol_TitleBg]                = ImVec4(0.60f, 0.60f, 0.60f, 1.00f); 
            colors[ImGuiCol_TitleBgActive]          = ImVec4(0.45f, 0.65f, 0.90f, 1.00f);
            colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.45f, 0.65f, 0.90f, 1.00f);
            colors[ImGuiCol_Header]                 = ImVec4(0.45f, 0.65f, 0.90f, 0.40f);
            colors[ImGuiCol_HeaderHovered]          = ImVec4(0.45f, 0.65f, 0.90f, 0.80f);
            colors[ImGuiCol_HeaderActive]           = ImVec4(0.45f, 0.65f, 0.90f, 1.00f);
            colors[ImGuiCol_Button]                 = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
            colors[ImGuiCol_ButtonHovered]          = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
            colors[ImGuiCol_ButtonActive]           = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
            colors[ImGuiCol_Tab]                    = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
            colors[ImGuiCol_TabHovered]             = ImVec4(0.45f, 0.65f, 0.90f, 0.80f);
            colors[ImGuiCol_TabActive]              = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
            colors[ImGuiCol_TabUnfocused]           = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
            colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
            colors[ImGuiCol_MenuBarBg]              = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
            style.WindowRounding = 0.0f;
            style.FrameRounding = 0.0f;
            style.ScrollbarRounding = 0.0f;
            style.GrabRounding = 0.0f;
            style.TabRounding = 0.0f;
            style.FrameBorderSize = 1.0f;
            break;

        case EditorTheme::Dark:
        default: 
            ImGui::StyleColorsDark(); 
            break;
    }
}

} // namespace Editor
