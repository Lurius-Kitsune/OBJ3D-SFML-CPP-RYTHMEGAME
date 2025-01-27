#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "TextureManager.h"

class MeshActor : public Actor
{
	MeshComponent* mesh;
	u_int renderMeshToken;

public:
	FORCEINLINE MeshComponent* GetMesh() const
	{
		return mesh;
	}
	FORCEINLINE void SetTextureRect(const Vector2i& _start, const Vector2i& _size)
	{
		SetTextureRect(IntRect(_start, _size));
	}
	FORCEINLINE void SetTextureRect(const IntRect& _rect)
	{
		M_TEXTURE.SetTextureRect(mesh->GetShape()->GetDrawable(), _rect);
	}

	#pragma region Modifier

	FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
	{
		Super::SetPosition(_position);
		mesh->GetShape()->SetPosition(_position);
	}
	FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
	{
		Super::SetRotation(_rotation);
		mesh->GetShape()->SetRotation(_rotation);
	}
	FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
	{
		Super::SetScale(_scale);
		mesh->GetShape()->SetScale(_scale);
	}
	FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
	{
		Super::SetOrigin(_origin);
		mesh->GetShape()->SetOrigin(_origin);
	}
	FORCEINLINE void SetOriginAtMiddle()
	{
		SetOrigin(mesh->GetShape()->GetDrawable()->getGeometricCenter());
	}
	FORCEINLINE virtual void Move(const Vector2f& _offset) override
	{
		Super::Move(_offset);
		mesh->GetShape()->Move(_offset);
	}
	FORCEINLINE virtual void Rotate(const Angle& _angle) override
	{
		Super::Rotate(_angle);
		mesh->GetShape()->Rotate(_angle);
	}
	FORCEINLINE virtual void Scale(const Vector2f& _factor) override
	{
		Super::Scale(_factor);
		mesh->GetShape()->Scale(_factor);
	}

	#pragma endregion

public:
	MeshActor() = default;
	MeshActor(const float _radius, const size_t& _pointCount = 30, const string& _path = "", const IntRect& _rect = {}, const string& _name = "MeshActor");
	MeshActor(const RectangleShapeData& _data, const string& _name = "MeshActor");
	MeshActor(const MeshActor& _other);

	

private:
	void RenderMesh(RenderWindow& _window);

public:
	virtual void Construct() override;
	virtual void Deconstruct() override;
};