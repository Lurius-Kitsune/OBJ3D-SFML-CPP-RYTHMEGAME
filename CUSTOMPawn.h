#pragma once
#include "Pawn.h"
#include "MeshComponent.h"
#include "CameraComponent.h"

class InputManager;

class CUSTOMPawn : public Pawn
{
	MeshComponent* mesh;
	Camera::CameraComponent* camera;

public:
	CUSTOMPawn(Level* _level, const string& _name = "CUSTOM Pawn");
	CUSTOMPawn(const CUSTOMPawn& _other);

protected:
	virtual void SetupInputController(Input::InputManager& _inputManager) override;
};