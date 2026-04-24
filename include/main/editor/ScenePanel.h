#pragma once
#include "main/editor/Panel.h"
#include <string>

namespace Editor {

class ScenePanel : public Panel {
public:
    ScenePanel(int screenWidth, int screenHeight);
    void OnImGui(World& world) override;

private:
    int screenWidth;
    int screenHeight;
    char filePathBuffer[256];
};

} // namespace Editor
