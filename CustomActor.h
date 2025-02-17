#pragma once
#include "Actor.h"
#include "CollisionComponent.h"

class CustomActor : public Actor
{
	CollisionComponent* collision;

public:
	CustomActor(Level* _level, const string& _name = "MeshActor");

};

