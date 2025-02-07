#include "GameMode.h"
#include "Engine.h"
#include "LevelManager.h"
#include "MeshActor.h"
#include "Particle.h"

void InitConfig()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Logger::Reset();
}

int main()
{
	InitConfig();

	Level* _level = new Level("LevelDemo");
	_level->SpawnActor<MeshActor>(RectangleShapeData({ 50.f, 50.f }, "Wall", JPG));
	_level->SpawnActor<ParticleActor>(1000, 3.0f);
	M_LEVEL.SetLevel(_level);

	Engine::GetInstance().Start();

	return EXIT_SUCCESS;
}