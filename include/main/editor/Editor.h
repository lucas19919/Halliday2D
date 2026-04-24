#pragma once
#include "main/World.h"
#include "main/editor/Panel.h"
#include "main/editor/EditorCamera.h"
#include "main/utility/InputHandler.h"
#include <vector>
#include <memory>

namespace Editor {

class Editor {
public:
    Editor(World& world, EditorCamera& camera, InputHandler& input);
    ~Editor();

    void Update(World& world);

private:
    std::vector<std::unique_ptr<Panel>> panels;
};

} // namespace Editor
