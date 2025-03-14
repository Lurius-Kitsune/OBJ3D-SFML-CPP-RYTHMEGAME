#pragma once 
#include "MeshActor.h"
#include "CollisionComponent.h"

class CUSTOMMesh : public MeshActor
{
	bool canMove;
	CollisionComponent* collision;
	
public:
	CUSTOMMesh(Level* _level, const RectangleShapeData& _data, const string& _name = "MeshActor");
	CUSTOMMesh(Level* _level, const CircleShapeData& _data, const string& _name = "MeshActor");

	virtual void Tick(const float _deltaTime) override;
	virtual void CollisionEnter(const CollisionData& _data) override;
};

