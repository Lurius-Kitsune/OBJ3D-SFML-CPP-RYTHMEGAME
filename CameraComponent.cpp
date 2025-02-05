#include "CameraComponent.h"
#include "Level.h"

CameraComponent::CameraComponent(Actor* _owner) : Component(_owner)
{
	const Vector2f& _windowSize = owner->GetLevel()->GetWindowSize();
	view = new View(_windowSize / 2.0f, _windowSize);
}

CameraComponent::CameraComponent(Actor* _owner, const Vector2f& _center, const Vector2f& _size) : Component(_owner)
{
	view = new View(_center, _size);
}

CameraComponent::CameraComponent(Actor* _owner, const Vector2f& _size) : Component(_owner)
{
	view = new View({ _size / 2.f }, _size);
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