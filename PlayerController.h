#pragma once

#include "CameraActor.h"
#include "InputManager.h"

using namespace Input;

class PlayerController
{
	SubclassOf<CameraActor>* camera;
	InputManager inputManager;

public:
	FORCEINLINE SubclassOf<CameraActor>* GetCamera() const
	{
		return camera;
	}
	FORCEINLINE InputManager& GetInputManager()
	{
		return inputManager;
	}

public:
	PlayerController();
	virtual ~PlayerController();
};

