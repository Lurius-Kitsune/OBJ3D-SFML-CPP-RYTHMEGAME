#pragma once
#include "Component.h"
#include "Actor.h"
class NoteMouvementComponent : public Component
{
	float speed;

public:
	NoteMouvementComponent(Actor* _owner, float _speed = 1.0f);

	virtual ~NoteMouvementComponent() = default;

public:
	virtual void Tick(const float _deltaTime) override;

private:
	void Move(const float _deltaTime);

};

