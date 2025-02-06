#pragma once
#include "Actor.h"
#include "MeshActor.h"
#include "LevelManager.h"

template<typename T>
class Spawner : public Actor
{
	float spawnRate;
	float spawnRange;

protected:
	SubclassOf<T>* ref;

public:
	Spawner(SubclassOf<T>* _ref) : Actor("Spawner")
	{
		spawnRate = 1.0f;
		spawnRange = 200.0f;
		ref = _ref;
	}

	Spawner(const Spawner<T>& _other) : Actor(_other)
	{
		spawnRate = _other.spawnRate;
		spawnRange = _other.spawnRange;
		ref = new SubclassOf<T>(*_other.ref);
	}
	~Spawner()
	{
		delete ref;
	}

private:
	virtual void BeginPlay() override
	{
		Super::BeginPlay();
		new Timer(bind(&Spawner::Spawn, this), Time(seconds(spawnRate)), true, true);
	}

	virtual void Spawn()
	{
		const Vector2f& _spawnPosition =
		{
			GetRandomNumberInRange(0.0f, spawnRange),
			GetRandomNumberInRange(0.0f, spawnRange),
		};
		ref->GetObject().SetPosition(_spawnPosition);

		M_LEVEL.GetCurrentLevel()->SpawnActor<T>(*ref);
	}
};