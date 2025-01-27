#include "RootComponent.h"

RootComponent::RootComponent(Actor* _owner, const TransformData& _transform) : Component(_owner)
{
	transform = _transform;
}

RootComponent::RootComponent(Actor* _owner, const RootComponent* _other) : Component(_owner)
{
	transform = _other->transform;
}