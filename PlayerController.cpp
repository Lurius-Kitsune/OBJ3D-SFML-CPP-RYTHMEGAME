#include "PlayerController.h"
#include "Level.h"

PlayerController::PlayerController(const string& _name) : Actor(_name)
{
	cameraRef = CameraActor(Vector2f(1200.0f, 600.0f), "PlayerCamera");
	camera = nullptr;
}

PlayerController::PlayerController(const PlayerController& _other) : Actor(_other)
{
	cameraRef = _other.cameraRef;
	camera = nullptr;
}

void PlayerController::Construct()
{
	Super::Construct();
	camera = level->SpawnCamera(cameraRef);
}


CameraActor* PlayerController::GetCamera()
{
	if (!camera)
	{
		camera = level->SpawnCamera(cameraRef);
	}

	return camera;
}