#include "VertexComponent.h"

VertexComponent::VertexComponent(Actor* _owner, const u_int& _count, const PrimitiveType& _type) 
							   : Component(_owner)
{
	vertex = new VertexObject(_count, _type);
}

VertexComponent::VertexComponent(Actor* _owner, const VertexComponent* _other) : Component(_owner)
{
	vertex = new VertexObject(*_other->vertex);
}

VertexComponent::~VertexComponent()
{
	delete vertex;
}