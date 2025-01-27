#include "CameraComponent.h"

CameraComponent::CameraComponent(Actor* _owner) : Component(_owner)
{
	view = new View();
}

CameraComponent::CameraComponent(Actor* _owner, const Vector2f& _center, const Vector2f& _size) : Component(_owner)
{
	view = new View(_center, _size);
}

CameraComponent::CameraComponent(Actor* _owner, const FloatRect& _rect) : Component(_owner)
{
	view = new View(_rect);
}

CameraComponent::CameraComponent(Actor* _owner, const CameraComponent* _other) : Component(_owner)
{
	view = new View(*_other->view);
}

CameraComponent::~CameraComponent()
{
	delete view;
}