#include "GameMode.h"

GameMode::GameMode()
{
	playerController = new PlayerController();
}

GameMode::~GameMode()
                  {
	delete playerController;
}
