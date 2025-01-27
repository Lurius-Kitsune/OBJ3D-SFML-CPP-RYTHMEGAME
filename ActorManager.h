#pragma once
#include "Singleton.h"
#include "Actor.h"

class ActorManager : public Singleton<ActorManager>
{
	set<Actor*> allActors;
	multimap<string, Actor*> actorsID;

public:
	FORCEINLINE set<Actor*> GetAllActors() const
	{
		return allActors;
	}
	FORCEINLINE void AddActor(Actor* _actor)
	{
		allActors.insert(_actor);
		actorsID.insert({ _actor->GetName(), _actor });
		_actor->BeginPlay();
	}
	FORCEINLINE void RemoveActor(Actor* _actor)
	{
		allActors.erase(_actor);

		const string& _actorName = _actor->GetName();
		using Iterator = multimap<string, Actor*>::iterator;
		const pair<Iterator, Iterator>& _results = actorsID.equal_range(_actorName);

		for (Iterator _it = _results.first; _it != _results.second; ++_it)
		{
			if (_it->second == _actor)
			{
				actorsID.erase(_it);
			}
		}

		_actor->BeginDestroy();
	}
	// duck_1
	FORCEINLINE string GetAvailableName(const string& _name, const int _index = 1)
	{
		// Je rajoute "_index" au nom actuel
		const string& _fullName = _name + "_" + to_string(_index);

		// Je parcours tous les Actors qui possèdent le même nom 
		using Iterator = multimap<string, Actor*>::iterator;
		const pair<Iterator, Iterator>& _results = actorsID.equal_range(_name);

		for (Iterator _it = _results.first; _it != _results.second; ++_it)
		{
			// Si c'est le même
			if (_it->second->GetName() == _fullName) continue;

			// Si aucun n'a le même nom, ce sera son nom
			return _fullName;
		}

		// Je reteste avec l'index suivant
		return GetAvailableName(_name, _index + 1);
	}

public:
	~ActorManager();

	void BeginPlay();
	void Tick(const float _deltaTime);
	void BeginDestroy();
};