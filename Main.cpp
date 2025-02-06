#include "GameMode.h"
#include "Engine.h"
#include "LevelManager.h"
#include "MeshActor.h"

void InitConfig()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Logger::Reset();
}

int main()
{
	InitConfig();

	Level* _test = new Level("test", new GameMode());
	_test->SpawnActor(MeshActor(RectangleShapeData({50.f, 50.f}, "Wall", JPG)));
	M_LEVEL.SetLevel(_test);
	_test->GetCameraManager().GetCurrent()->Zoom(1.5f);
	Engine::GetInstance().Start();


	return EXIT_SUCCESS;
}