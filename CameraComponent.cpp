#include "CameraComponent.h"
#include "Level.h"

Camera::CameraComponent::CameraComponent(Actor* _owner) : Component(_owner)
{
	const Vector2f& _windowSize = owner->GetLevel()->GetWindowSize();
	view = new View(_windowSize / 2.0f, _windowSize);
}

Camera::CameraComponent::CameraComponent(Actor* _owner, const Vector2f& _center, const Vector2f& _size) : Component(_owner)
{
	view = new View(_center, _size);
}

Camera::CameraComponent::CameraComponent(Actor* _owner, const Vector2f& _size) : Component(_owner)
{
	view = new View({ _size / 2.0f }, _size);
}

Camera::CameraComponent::CameraComponent(Actor* _owner, const FloatRect& _rect) : Component(_owner)
{
	view = new View(_rect);
}

Camera::CameraComponent::CameraComponent(Actor* _owner, const CameraComponent& _other) : Component(_owner)
{
	view = new View(*_other.view);
}

Camera::CameraComponent::~CameraComponent()
{
	delete view;
}