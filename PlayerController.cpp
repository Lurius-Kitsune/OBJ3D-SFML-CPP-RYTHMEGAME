#include "PlayerController.h"
#include "Level.h"
#include "Pawn.h"

using namespace Input;

PlayerController::PlayerController(Level* _level, const string& _name) : Actor(_level, _name)
{
	inputManager = Input::InputManager();
	window = &_level->GetRenderWindow();
	cameraManager = &_level->GetCameraManager();
	pawn = nullptr;
}

PlayerController::PlayerController(const PlayerController& _other) : Actor(_other)
{
	inputManager = _other.inputManager;
	window = _other.window;
	cameraManager = _other.cameraManager;
	pawn = _other.pawn;
}


void PlayerController::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

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

Vector2f PlayerController::GetPixelToCoords() const
{
	const Vector2i& _pixelPos = Mouse::getPosition(*window);
	const Vector2f& _pixelToCoords = window->mapPixelToCoords(_pixelPos, *cameraManager->GetCurrent()->GetView());
	return _pixelToCoords;
}

Pawn* PlayerController::GetPawnRef() const
{
	return new Pawn(level);
}