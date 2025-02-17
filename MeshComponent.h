#pragma once
#include "Component.h"
#include "ShapeObject.h"

class Actor;

class MeshComponent : public Component
{
	u_int renderMeshToken;
	ShapeObject* shape;

public:
	FORCEINLINE void SetShape(ShapeObject* _shape)
	{
		shape = _shape;
	}
	FORCEINLINE u_int GetRenderMeshToken() const
	{
		return renderMeshToken;
	}
	FORCEINLINE ShapeObject* GetShape() const
	{
		return shape;
	}
	FORCEINLINE virtual Component* Clone(Actor* _owner) const override
	{
		return new MeshComponent(_owner, *this);
	}

public:
	MeshComponent(Actor* _owner, const CircleShapeData& _data);
	MeshComponent(Actor* _owner, const RectangleShapeData& _data);
	MeshComponent(Actor* _owner, const MeshComponent& _other);
	~MeshComponent();

	virtual void Construct() override;
	virtual void Deconstruct() override;

	void SetOriginAtMiddle();
	void RenderMesh(RenderWindow& _window);
};