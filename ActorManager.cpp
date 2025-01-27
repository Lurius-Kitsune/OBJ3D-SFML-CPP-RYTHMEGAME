#include "ActorManager.h"

ActorManager::~ActorManager()
{
	for (Actor* _actor : allActors)
	{
		delete _actor;
	}
}


void ActorManager::BeginPlay()
{
	for (Actor* _actor : allActors)
	{
		_actor->BeginPlay();
	}
}

void ActorManager::Tick(const float _deltaTime)
{
	vector<Actor*> _garbage;

	for (Actor* _actor : allActors)
	{
		_actor->Tick(_deltaTime);

		if (_actor->IsToDelete())
		{
			_garbage.push_back(_actor);
		}
	}

	for (Actor* _actor : _garbage)
	{
		_actor->Deconstruct();
		delete _actor;
	}
}

void ActorManager::BeginDestroy()
{
	for (Actor* _actor : allActors)
	{
		_actor->BeginDestroy();
	}
}