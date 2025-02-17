#include "GameMode.h"
#include "Level.h"
#include "Pawn.h"

GameMode::GameMode(Level* _level, const string& _name) : Actor(_level, _name)
{
	controller = nullptr;
	hud = nullptr;
	isSplitScreen = false;
}

GameMode::GameMode(const GameMode& _other) : Actor(_other)
{
	controller = nullptr;
	hud = nullptr;
	isSplitScreen = false;
}


void GameMode::Possess(Pawn* _pawn)
{
	if(controller)
	{
		controller->Disable();
	}
	controller = _pawn->GetController();
	controller->Enable();
}

void GameMode::Unpossess(Pawn* _pawn)
{
	if (controller)
	{
		controller->Disable();
		controller = nullptr;
	}
}
