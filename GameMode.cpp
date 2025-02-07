#include "GameMode.h"
#include "Level.h"

GameMode::GameMode(Level* _level, const string& _name) : Actor(_level, _name)
{
	controllerRef = PlayerController(_level);
	controller = nullptr;
	hudRef = HUD(_level);
	hud = nullptr;
}

GameMode::GameMode(const GameMode& _other) : Actor(_other)
{
	controllerRef = _other.controllerRef;
	controller = nullptr;
	hudRef = _other.hudRef;
	hud = nullptr;
}


void GameMode::Construct()
{
	Super::Construct();

	controller = GetPlayerController();
	hud = GetHUD();
}

PlayerController* GameMode::GetPlayerController()
{
	if (!controller)
	{
		controller = level->SpawnActor<PlayerController>(controllerRef);
	}

	return controller;
}

UI::HUD* GameMode::GetHUD()
{
	if (!hud)
	{
		hud = level->SpawnActor<HUD>(hudRef);
	}

	return hud;
}