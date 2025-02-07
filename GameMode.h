#pragma once
#include "Actor.h"
#include "PlayerController.h"
#include "HUD.h"

using namespace UI;

class GameMode : public Actor
{
	SubclassOf<PlayerController> controllerRef;
	PlayerController* controller;
	SubclassOf<HUD> hudRef;
	HUD* hud;

public:
	GameMode(Level* _level, const string& _name = "GameMode");
	GameMode(const GameMode& _other);

	virtual void Construct() override;
	PlayerController* GetPlayerController();
	HUD* GetHUD();
};