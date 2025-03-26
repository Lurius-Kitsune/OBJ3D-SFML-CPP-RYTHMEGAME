#pragma once
#include "Actor.h"
#include "PlayerController.h"

class InputManager;

class Pawn : public Actor
{
protected:
	PlayerController* controller;

public:
	FORCEINLINE PlayerController* GetController() const
	{
		return controller;
	}
public:
	Pawn(Level* _level, const string& _name = "Pawn");
	Pawn(const Pawn& _other);

protected:
	virtual void SetupInputController(Input::InputManager& _inputManager) {};

public:
	virtual void Construct() override;
};