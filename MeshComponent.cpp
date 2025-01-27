#include "MeshComponent.h"

MeshComponent::MeshComponent(Actor* _owner, const float _radius, const size_t& _pointCount,
							 const string& _path, const IntRect& _rect)
						   : Component(_owner)
{
	shape = new ShapeObject(_radius, _path, _rect, _pointCount);
}

MeshComponent::MeshComponent(Actor* _owner, const RectangleShapeData& _data) : Component(_owner)
{
	shape = new ShapeObject(_data);
}

MeshComponent::MeshComponent(Actor* _owner, const MeshComponent* _other) : Component(_owner) 
{
	shape = new ShapeObject(*_other->shape);
}


MeshComponent::~MeshComponent()
{
	delete shape;
}