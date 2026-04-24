#pragma once
#include "main/editor/Panel.h"
#include "main/editor/EditorCamera.h"
#include "main/utility/InputHandler.h"

namespace Editor {

class PerformancePanel : public Panel {
public:
    PerformancePanel(EditorCamera& camera, InputHandler& input);
    void OnImGui(World& world) override;

private:
    EditorCamera& camera;
    InputHandler& input;
};

} // namespace Editor
