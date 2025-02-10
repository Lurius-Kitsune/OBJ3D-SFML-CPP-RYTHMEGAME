#pragma once
#include "Component.h"
#include "ShapeObject.h"

class Actor;

class MeshComponent : public Component
{
	ShapeObject* shape;

public:
	FORCEINLINE ShapeObject* GetShape() const
	{
		return shape;
	}
	FORCEINLINE void SetShape(ShapeObject* _shape)
	{
		shape = _shape;
	}

	FORCEINLINE Component* Clone(Actor* _owner) const override
	{
		return new MeshComponent(_owner, *this);
	}

public:
	MeshComponent(Actor* _owner, const CircleShapeData& _data);
	MeshComponent(Actor* _owner, const RectangleShapeData& _data);
	MeshComponent(Actor* _owner, const MeshComponent& _other);
	~MeshComponent();
};