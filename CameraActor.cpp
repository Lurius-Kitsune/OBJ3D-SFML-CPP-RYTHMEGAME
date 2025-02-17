#include "CameraActor.h"

Camera::CameraActor::CameraActor(Level* _level, const string& _name) : Actor(_level, _name)
{
	camera = CreateComponent<CameraComponent>();
}

Camera::CameraActor::CameraActor(Level* _level, const Vector2f& _center, const Vector2f& _size, const string& _name) : Actor(_level, _name)
{
	camera = CreateComponent<CameraComponent>(_center, _size);
}

Camera::CameraActor::CameraActor(Level* _level, const Vector2f& _size, const string& _name) : Actor(_level, _name)
{
	camera = CreateComponent<CameraComponent>(_size);
}

Camera::CameraActor::CameraActor(Level* _level, const FloatRect& _rect, const string& _name) : Actor(_level, _name)
{
	camera = CreateComponent<CameraComponent>(_rect);
}

Camera::CameraActor::CameraActor(const CameraActor& _other) : Actor(_other)
{
	camera = CreateComponent<CameraComponent>(*_other.camera);
}