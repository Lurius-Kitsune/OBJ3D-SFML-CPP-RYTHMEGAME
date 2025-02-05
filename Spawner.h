#pragma once
#include "Actor.h"
#include "MeshActor.h"
#include "Level.h"

class Spawner : public Actor
{
	float spawnRate;
	float spawnRange;
	SubclassOf<MeshActor>* ref;

public:
	Spawner(Level* _level);
	Spawner(const Spawner& _other);
	~Spawner();

private:
	virtual void BeginPlay() override;
	void Spawn();
};