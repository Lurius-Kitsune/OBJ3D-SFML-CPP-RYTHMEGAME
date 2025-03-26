#include "CUSTOMHUD.h"
#include "Level.h"

CUSTOMHUD::CUSTOMHUD(Level* _level) : HUD(_level)
{
	// Test pour avoir un feedback sur le hud
	mesh = _level->SpawnActor<MeshActor>(CircleShapeData(10.0f));
	mesh->SetPosition(Vector2f(10.0f, 10.0f));
}

CUSTOMHUD::CUSTOMHUD(const CUSTOMHUD& _other) : HUD(_other)
{
	mesh = _other.mesh;
}
