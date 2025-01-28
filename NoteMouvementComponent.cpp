#include "NoteMouvementComponent.h"


NoteMouvementComponent::NoteMouvementComponent(Actor* _owner, float _speed)
	: Component(_owner)
{
	speed = _speed;
}

NoteMouvementComponent::NoteMouvementComponent(Actor* _owner, const NoteMouvementComponent& _other)
	: Component(_owner)
{
	speed = _other.speed;
}

void NoteMouvementComponent::Tick(const float _deltaTime)
{
	Move(_deltaTime);
}

void NoteMouvementComponent::Move(const float _deltaTime)
{
	owner->Move(Vector2f(0, 1.0f) * speed * _deltaTime * 500.0f);
}
