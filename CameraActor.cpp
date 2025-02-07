#include "CameraActor.h"

CameraActor::CameraActor(const string& _name) : Actor(_name)
{
	camera = CreateComponent<CameraComponent>();
}

CameraActor::CameraActor(const Vector2f& _center, const Vector2f& _size, const string& _name) : Actor(_name)
{
	camera = CreateComponent<CameraComponent>(_center, _size);
}

CameraActor::CameraActor(const Vector2f& _size, const string& _name) : Actor(_name)
{
	camera = CreateComponent<CameraComponent>(_size);
}

CameraActor::CameraActor(const FloatRect& _rect, const string& _name) : Actor(_name)
{
	camera = CreateComponent<CameraComponent>(_rect);
}

CameraActor::CameraActor(const CameraActor& _other) : Actor(_other)
{
	camera = CreateComponent<CameraComponent>(_other.camera);
}