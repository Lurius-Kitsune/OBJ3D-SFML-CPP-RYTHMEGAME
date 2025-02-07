#include "MeshComponent.h"

MeshComponent::MeshComponent(Actor* _owner, const CircleShapeData& _data) : Component(_owner)
{
	shape = new ShapeObject(_data);
}

MeshComponent::MeshComponent(Actor* _owner, const RectangleShapeData& _data) : Component(_owner)
{
	shape = new ShapeObject(_data);
}

MeshComponent::MeshComponent(Actor* _owner, const MeshComponent& _other) : Component(_owner) 
{
	shape = new ShapeObject(*_other.shape);
}


MeshComponent::~MeshComponent()
{
	delete shape;
}