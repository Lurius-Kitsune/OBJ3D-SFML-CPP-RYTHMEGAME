#pragma once
#include "CoreMinimal.h"
#include "TransformData.h"

class ITransformableModifier
{
public:
	FORCEINLINE virtual void SetPosition(const Vector2f& _position) = 0;
	FORCEINLINE virtual void SetRotation(const Angle& _rotation) = 0;
	FORCEINLINE virtual void SetScale(const Vector2f& _scale) = 0;
	FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) = 0;
	FORCEINLINE virtual void SetTransform(const TransformData& _transformData)
	{
		SetPosition(_transformData.position);
		SetRotation(_transformData.rotation);
		SetScale(_transformData.scale);
		SetOrigin(_transformData.origin);
	}
	FORCEINLINE virtual void Move(const Vector2f& _offset) = 0;
	FORCEINLINE virtual void Rotate(const Angle& _angle) = 0;
	FORCEINLINE virtual void Scale(const Vector2f& _factor) = 0;
};