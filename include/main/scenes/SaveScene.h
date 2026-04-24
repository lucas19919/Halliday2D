#pragma once
#include <string>
#include <external/nlohmann/json.hpp>
#include "main/World.h"

class SaveScene
{
public:
    static void Save(const std::string& filePath, World& world);

private:
    static nlohmann::json SerializeObject(GameObject* obj);
    static nlohmann::json SerializeConstraints(const std::vector<std::unique_ptr<Constraint>>& constraints);
    static nlohmann::json SerializeControllers(const std::vector<std::unique_ptr<Controller>>& controllers);
};
