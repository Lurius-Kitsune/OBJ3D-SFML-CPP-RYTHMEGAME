#pragma once
#include "MeshActor.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Duck : public MeshActor
{
	MovementComponent* movement;
	AnimationComponent* animation;

public:
	FORCEINLINE MovementComponent* GetMovement() const
	{
		return movement;
	}

public:
	Duck(const Vector2f& _size, const string& _path = "", const IntRect& _rect = {});
	Duck(const Duck& _other);

protected:
	virtual void BeginPlay() override;
public:
	virtual void Construct() override;
	virtual void Deconstruct() override;
};