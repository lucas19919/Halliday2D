#pragma once
#include "main/GameObject.h"
#include "math/Vec2.h"

enum class GizmoType { NONE, TRANSLATE, ROTATE, SCALE };
enum class GizmoAxis { NONE, X, Y, BOTH };

class EditorState {
public:
    static EditorState& Get() {
        static EditorState instance;
        return instance;
    }

    void SetSelected(GameObject* obj) { selectedObject = obj; }
    GameObject* GetSelected() const { return selectedObject; }

    void SetGizmoType(GizmoType type) { activeGizmoType = type; }
    GizmoType GetGizmoType() const { return activeGizmoType; }

    void SetHoveredAxis(GizmoAxis axis) { hoveredAxis = axis; }
    GizmoAxis GetHoveredAxis() const { return hoveredAxis; }

    void SetActiveAxis(GizmoAxis axis) { activeAxis = axis; }
    GizmoAxis GetActiveAxis() const { return activeAxis; }

    bool IsGizmoHovered() const { return hoveredAxis != GizmoAxis::NONE; }
    bool IsGizmoActive() const { return activeAxis != GizmoAxis::NONE; }

    void SetActiveScenePath(const std::string& path) { currentScenePath = path; }
    const std::string& GetActiveScenePath() const { return currentScenePath; }

    void SetViewportMousePos(Vector2 pos) { viewportMousePos = pos; }
    Vector2 GetViewportMousePos() const { return viewportMousePos; }

    void SetViewportSize(Vector2 size) { viewportSize = size; }
    Vector2 GetViewportSize() const { return viewportSize; }

    void SetViewportHovered(bool hovered) { isViewportHovered = hovered; }
    bool IsViewportHovered() const { return isViewportHovered; }

    void SetViewportFocused(bool focused) { isViewportFocused = focused; }
    bool IsViewportFocused() const { return isViewportFocused; }

private:
    EditorState() : selectedObject(nullptr), activeGizmoType(GizmoType::TRANSLATE), hoveredAxis(GizmoAxis::NONE), activeAxis(GizmoAxis::NONE), currentScenePath("../assets/examples/PrattTruss.json"), viewportMousePos{0,0}, viewportSize{0,0}, isViewportHovered(false), isViewportFocused(false) {}
    GameObject* selectedObject;
    GizmoType activeGizmoType;
    GizmoAxis hoveredAxis;
    GizmoAxis activeAxis;
    std::string currentScenePath;

    Vector2 viewportMousePos;
    Vector2 viewportSize;
    bool isViewportHovered;
    bool isViewportFocused;
};
