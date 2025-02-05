#include "PlayerController.h"

PlayerController::PlayerController()
{
	camera = new SubclassOf(CameraActor({1200, 600}, "PlayerCamera"));
}

PlayerController::~PlayerController()
  {
	delete camera;
}
