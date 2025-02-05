#include "Spawner.h"
#include "TimerManager.h"

Spawner::Spawner(Level* _level) : Actor("Spawner")
{
	spawnRate = 1.0f;
	spawnRange = 200.0f;
	ref = new SubclassOf(MeshActor(CircleShapeData(20.0f, "Charm")));
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

	level->SpawnActor<MeshActor>(*ref);
}