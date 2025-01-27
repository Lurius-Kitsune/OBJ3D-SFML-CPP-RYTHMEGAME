#pragma once
#include "Component.h"
#include "TransformableModifier.h"
#include "TransformableViewer.h"

enum AttachmentType
{
	AT_KEEP_RELATIVE,
	AT_KEEP_WORLD,
	AT_SNAP_TO_TARGET,
};

class RootComponent : public Component, public ITransformableModifier, public ITransformableViewer
{
	TransformData transform;

public:
	#pragma region Getters

	FORCEINLINE virtual Vector2f GetOrigin() const override
	{
		return transform.origin;
	}
	FORCEINLINE virtual Vector2f GetPosition() const override
	{
		return transform.position;
	}
	FORCEINLINE virtual Angle GetRotation() const override
	{
		return transform.rotation;
	}
	FORCEINLINE virtual Vector2f GetScale() const override
	{
		return transform.scale;
	}
	FORCEINLINE virtual TransformData GetTransform() const override
	{
		return transform;
	}

	#pragma endregion

	#pragma region Setters

	FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
	{
		transform.origin = _origin;
	}
	FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
	{
		transform.position = _position;
	}
	FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
	{
		transform.rotation = _rotation;
	}
	FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
	{
		transform.scale = _scale;
	}
	FORCEINLINE virtual void SetTransform(const TransformData& _transformData) override
	{
		transform = _transformData;
	}
	FORCEINLINE virtual void Move(const Vector2f& _offset) override
	{
		transform.position += _offset;
	}
	FORCEINLINE virtual void Rotate(const Angle& _angle) override
	{
		transform.rotation += _angle;
	}
	FORCEINLINE virtual void Scale(const Vector2f& _factor) override
	{
		transform.scale += _factor;
	}

	#pragma endregion

public:
	RootComponent(Actor* _owner, const TransformData& _transform = {});
	RootComponent(Actor* _owner, const RootComponent* _other);
};