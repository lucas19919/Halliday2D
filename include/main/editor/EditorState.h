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

    void SetViewportMousePos(Vec2 pos) { viewportMousePos = pos; }
    Vec2 GetViewportMousePos() const { return viewportMousePos; }

    void SetViewportSize(Vec2 size) { viewportSize = size; }
    Vec2 GetViewportSize() const { return viewportSize; }

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

    Vec2 viewportMousePos;
    Vec2 viewportSize;
    bool isViewportHovered;
    bool isViewportFocused;
    };
