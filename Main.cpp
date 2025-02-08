#include "Engine.h"
#include "LevelManager.h"
#include "SelectLevel.h"

void InitConfig()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Logger::Reset();
}

int main()
{
	InitConfig();

	SelectLevel* _level = new SelectLevel();
	M_LEVEL.SetLevel(_level);

	Engine::GetInstance().Start();

	return EXIT_SUCCESS;
}