#include "Component.h"
#include "Actor.h"

Component::Component(Actor* _owner)
{
	owner = _owner;
	SetActive(true);
}

Component::Component(Actor* _owner, const Component& _other)
{
	owner = _owner;
}