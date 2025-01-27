#pragma once
#include "Actor.h"
#include "MeshActor.h"

class Spawner : public Actor
{
	float spawnRate;
	float spawnRange;
	SubclassOf<MeshActor>* ref;

public:
	Spawner();
	Spawner(const Spawner& _other);
	~Spawner();

private:
	virtual void BeginPlay() override;
	void Spawn();
};