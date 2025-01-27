#include "GameManager.h"

GameManager::~GameManager()
{
	delete currentGame;
}


void GameManager::Launch(Game* _currentGame)
{
	if (!(currentGame = _currentGame)) return;

	currentGame->Start();
	while (!currentGame->Update());
	currentGame->Stop();
}