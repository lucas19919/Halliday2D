#include "main/utility/InputHandler.h"
#include "main/components/Controller.h"
#include "main/physics/Config.h"
#include "main/editor/EditorState.h"
#include "raylib.h"
#include "external/imgui/imgui.h"

void InputHandler::Update(World& world, EditorCamera& camera, const std::string& filePath, int screenWidth, int screenHeight, float dt)
{
    EditorState& state = EditorState::Get();

    // Ignore input if ImGui is capturing, UNLESS it's the viewport
    if (ImGui::GetCurrentContext() != nullptr && ImGui::GetIO().WantCaptureMouse && !state.IsViewportHovered()) return;

    // Update mouse position in physics world using viewport-relative coordinates
    physicsMousePos = camera.ScreenToWorldMeters(state.GetViewportMousePos());

    // Selection logic
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && state.IsViewportHovered())
    {
        // Don't change selection if clicking on a gizmo
        if (!state.IsGizmoHovered() && !state.IsGizmoActive())
        {
            GameObject* hit = nullptr;
            // Iterate backwards to select "top" objects first if they overlap
            const auto& objects = world.GetGameObjects();
            for (auto it = objects.rbegin(); it != objects.rend(); ++it)
            {
                GameObject* obj = it->get();
                if (obj->c && obj->c->TestPoint(physicsMousePos))
                {
                    hit = obj;
                    break;
                }
            }
            EditorState::Get().SetSelected(hit);
        }
    }

    // Camera Controls
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
    {
        Vector2 delta = GetMouseDelta();
        camera.Pan(Vec2(delta.x, delta.y));
    }

    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        Vector2 m = GetMousePosition();
        camera.Zoom(wheel, Vec2(m.x, m.y));
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        world.isPaused = !world.isPaused;
    }
    if (IsKeyPressed(KEY_R))
    {
        world.isPaused = true;
        world.Clear();
        LoadScene::Load(filePath, world, screenWidth, screenHeight);
    }

    if (IsKeyPressed(KEY_G))
    {
        EditorState::Get().SetGizmoType(GizmoType::TRANSLATE);
    }
    if (IsKeyPressed(KEY_E))
    {
        EditorState::Get().SetGizmoType(GizmoType::ROTATE);
    }
    if (IsKeyPressed(KEY_S))
    {
        EditorState::Get().SetGizmoType(GizmoType::SCALE);
    }

    for (const auto& c : world.GetControllers())
    {
        if (c->active)
            c->Update(dt); 
    }
}
