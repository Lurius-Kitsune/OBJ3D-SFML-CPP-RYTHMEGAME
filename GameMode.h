#pragma once
#include "Actor.h"
#include "PlayerController.h"

class GameMode : public Actor
{
	SubclassOf<PlayerController> controllerRef;
	PlayerController* controller;
	/*SubclassOf<HUD>* hudRef;
	HUD* hud;*/

public:
	/*FORCEINLINE HUD* GetHUD() const
	{
		if (!hud)
		{
			hud = SpawnActor<HUD>(hudRef);
		}

		return hud;
	}*/

public:
	GameMode(const string& _name = "GameMode");
	GameMode(const GameMode& _other);

	virtual void Construct() override;
	PlayerController* GetPlayerController();
};