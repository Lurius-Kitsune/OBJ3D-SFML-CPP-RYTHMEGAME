#include "PlayerController.h"
#include "Level.h"
#include "Pawn.h"

using namespace Input;

PlayerController::PlayerController(Level* _level, const string& _name) : Actor(_level, _name)
{
	window = &_level->GetRenderWindow();
	pawn = nullptr;
}

PlayerController::PlayerController(const PlayerController& _other) : Actor(_other)
{
	window = _other.window;
	pawn = _other.pawn;
}


void PlayerController::Tick(const float _deltaTime)
{
	inputManager.Update(*window);
}

void PlayerController::Enable()
{
	for (const pair<string, ActionMap*>& _pair : inputManager.GetActionMaps())
	{
		ActionMap* _actionMap = _pair.second;
		_actionMap->Enable();
	}
}

void PlayerController::Disable()
{
	for (const pair<string, ActionMap*>& _pair : inputManager.GetActionMaps())
	{
		ActionMap* _actionMap = _pair.second;
		_actionMap->Disable();
	}
}

Pawn* PlayerController::GetPawnRef() const
{
	return new Pawn(level);
}