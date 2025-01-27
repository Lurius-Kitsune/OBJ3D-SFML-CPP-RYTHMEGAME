#include "Spawner.h"
#include "TimerManager.h"
#include "Level.h"

Spawner::Spawner() : Actor("Spawner")
{
	spawnRate = 1.0f;
	spawnRange = 200.0f;
	ref = new SubclassOf<MeshActor>(MeshActor(20.0f, 30, "Charm"));
}

Spawner::Spawner(const Spawner& _other) : Actor(_other)
{
	spawnRate = _other.spawnRate;
	spawnRange = _other.spawnRange;
	ref = new SubclassOf<MeshActor>(*_other.ref);
}

Spawner::~Spawner()
{
	delete ref;
}


void Spawner::BeginPlay()
{
	Super::BeginPlay();
	new Timer(bind(&Spawner::Spawn, this), Time(seconds(spawnRate)), true, true);
}

void Spawner::Spawn()
{
	LOG(Display, "Spawn");

	const Vector2f& _spawnPosition =
	{
		GetRandomNumberInRange(0.0f, spawnRange),
		GetRandomNumberInRange(0.0f, spawnRange),
	};
	ref->GetObject().SetPosition(_spawnPosition);

	Level::SpawnActor<MeshActor>(*ref);
}