#pragma once

namespace Editor {

enum class EditorTheme {
    Dark,
    Light,
    Retro
};

class ThemeManager {
public:
    static void ApplyTheme(EditorTheme theme);
};

} // namespace Editor
