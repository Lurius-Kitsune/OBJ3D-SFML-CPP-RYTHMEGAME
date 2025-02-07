#pragma once
#include "Actor.h"
#include "VertexComponent.h"

class VertexActor : public Actor
{
	VertexComponent* vertex;
	u_int renderMeshToken;

public:
	FORCEINLINE Vertex& GetVertexByIndex(const u_int& _index)
	{
		return vertex->GetVertex()->GetVertexByIndex(_index);
	}

public:
	VertexActor(const u_int& _count, const PrimitiveType& _type = PrimitiveType::Points, const string& _name = "VertexActor");
	VertexActor(const VertexActor& _other);

	virtual void Construct() override;
	virtual void Deconstruct() override;
	virtual void RenderVertices(RenderWindow& _window);
};