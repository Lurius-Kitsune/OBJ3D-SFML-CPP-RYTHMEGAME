#include "Actor.h"
#include "ActorManager.h"
#include "TimerManager.h"
#include "Level.h"

Actor::Actor(const string& _name, const TransformData& _transform)
{
	isToDelete = false;
	id = 0;
	lifeSpan = 0.0f;
	name = _name;
	displayName = "Unknown";
	components = set<Component*>();
	root = CreateComponent<RootComponent>(_transform);
	parent = nullptr;
	attachment = AT_NONE;
	children = set<Actor*>();
	level = nullptr;
}

Actor::Actor(const Actor& _other)
{
	isToDelete = _other.isToDelete;
	id = _other.id;
	lifeSpan = _other.lifeSpan;
	name = _other.name;
	displayName = _other.displayName;
	for (Component* _component : _other.components)
	{
		CreateComponent<TYPE(*_component)>(*_component);
	}
	root = GetComponent<RootComponent>();
	parent = _other.parent;
	attachment = _other.attachment;
	for (Actor* _child : _other.children)
	{
		TYPE(_child)* _actor = new TYPE(_child)(_child);
		children.insert(*_actor);
	}
	level = _other.level;
}

Actor::~Actor()
{
	for (Component* _component : components)
	{
		delete _component;
	}
}


void Actor::Construct()
{
	if (!level)
	{
		LOG(Fatal, "Tried to construct an actor (\"" + name + "\") with no level associated !");
		return;
	}

	id = GetUniqueID();
	displayName = level->GetActorManager().GetAvailableName(name);
	SetActive(true);
	level->GetActorManager().AddActor(this);
 }

void Actor::Deconstruct()
{
	SetActive(false);
	level->GetActorManager().RemoveActor(this);
}

void Actor::BeginPlay()
{
	if (lifeSpan > 0.0f)
	{
		new Timer(bind(&Actor::Destroy, this), seconds(lifeSpan), true);
	}

	for (Component* _component : components)
	{
		_component->BeginPlay();
	}
}

void Actor::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	for (Component* _component : components)
	{
		_component->Tick(_deltaTime);
	}
}

void Actor::BeginDestroy()
{
	for (Component* _component : components)
	{
		_component->BeginDestroy();
	}
}


void Actor::SetName(const string& _name)
{
	if (name == _name) return;
	name = _name;
	displayName = level->GetActorManager().GetDisplayName(this);
}

void Actor::Destroy()
{
	SetToDelete();
}

void Actor::AddComponent(Component* _component)
{
	components.insert(_component);
}

void Actor::RemoveComponent(Component* _component)
{
	components.erase(_component);
}