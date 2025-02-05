#pragma once

#include "PlayerController.h"

class GameMode
{
	PlayerController* playerController;

public:
	FORCEINLINE PlayerController* GetPlayerController() const
	{
		return playerController;
	}

public:
	GameMode();
	virtual ~GameMode();
};

