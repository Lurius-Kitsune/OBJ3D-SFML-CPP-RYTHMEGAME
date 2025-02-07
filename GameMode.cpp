#include "GameMode.h"
#include "Level.h"

GameMode::GameMode(const string& _name) : Actor(_name)
{
	controllerRef = PlayerController();
	controller = nullptr;
}

GameMode::GameMode(const GameMode& _other) : Actor(_other)
{
	controllerRef = _other.controllerRef;
	controller = nullptr;
}


void GameMode::Construct()
{
	Super::Construct();
	controller = level->SpawnActor<PlayerController>(controllerRef);
}

PlayerController* GameMode::GetPlayerController()
{
	if (!controller)
	{
		controller = level->SpawnActor<PlayerController>(controllerRef);
	}

	return controller;
}