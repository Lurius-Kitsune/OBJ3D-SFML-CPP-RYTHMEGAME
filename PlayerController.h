#pragma once
#include "Actor.h"
#include "CameraActor.h"
#include "InputManager.h"

using namespace Input;

class PlayerController : public Actor
{
	SubclassOf<CameraActor> cameraRef;
	CameraActor* camera;
	InputManager inputManager;

public:
	FORCEINLINE InputManager& GetInputManager()
	{
		return inputManager;
	}

public:
	PlayerController(const string& _name = "PlayerController");
	PlayerController(const PlayerController& _other);
	virtual void Construct() override;

	CameraActor* GetCamera();
};