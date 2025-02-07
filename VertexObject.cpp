#include "VertexObject.h"

VertexObject::VertexObject(const u_int& _count, const PrimitiveType& _type)
{
	vertices = new VertexArray(_type, _count);
}

VertexObject::VertexObject(const VertexObject& _other)
{
	vertices = new VertexArray(*_other.vertices);
}

VertexObject::~VertexObject()
{
	delete vertices;
}