#include "Pawn.h"
#include "InputManager.h"
#include "Level.h"

Pawn::Pawn(Level* _level, const string& _name) : Actor(_level, _name)
{
	controller = _level->GetGameMode()->GetPlayerController();
}

Pawn::Pawn(const Pawn& _other) : Actor(_other)
{
	controller = _other.controller;
}


void Pawn::Construct()
{
	Super::Construct();

	Input::InputManager& _inputManager = controller->GetInputManager();
	SetupInputController(_inputManager);
}