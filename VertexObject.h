#pragma once
#include "Object.h"

/*
void ParticleSystem::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = nullptr;
	target.draw(vertices, states);
}
*/

class VertexObject : public Object
{
	VertexArray* vertices;

public:
	FORCEINLINE Vertex& GetVertexByIndex(const u_int& _index)
	{
		return (*vertices)[_index];
	}
	FORCEINLINE virtual VertexArray* GetDrawable() const override
	{
		return vertices;
	}

public:
	VertexObject(const u_int& _count, const PrimitiveType& _type = PrimitiveType::Points);
	VertexObject(const VertexObject& _other);
	~VertexObject();
};