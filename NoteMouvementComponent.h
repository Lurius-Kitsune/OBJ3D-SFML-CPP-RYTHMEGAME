#pragma once
#include "Component.h"
#include "Actor.h"
class NoteMouvementComponent : public Component
{
	float speed;
	Actor* triggerNote;
	Vector2f direction;

public:
	NoteMouvementComponent(Actor* _owner, Actor* _triggerNote = nullptr,const float _speed = 1.0f);
	NoteMouvementComponent(Actor* _owner, const NoteMouvementComponent& _other);

	virtual ~NoteMouvementComponent() = default;

public:
	virtual void Tick(const float _deltaTime) override;

private:
	void Move(const float _deltaTime);

};

