#pragma once
#include "main/GameObject.h"
#include "main/World.h"
#include "raylib.h"

void Render(World& world);
static void DrawContact(const ContactConstraint& contact);