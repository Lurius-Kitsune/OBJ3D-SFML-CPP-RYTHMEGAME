#include "Actor.h"
#include "ActorManager.h"
#include "TimerManager.h"
#include "Level.h"

Actor::Actor(Level* _level, const string& _name, const TransformData& _transform)
{
	level = _level; // Setup level in first

	isToDelete = false;
	id = 0;
	lifeSpan = 0.0f;
	name = _name;
	displayName = "Unknown";
	components = map<type_index, Component*>();
	root = CreateComponent<RootComponent>(_transform);
	parent = nullptr;
	attachment = AT_NONE;
	children = set<Actor*>();
}

Actor::Actor(const Actor& _other)
{
	isToDelete = _other.isToDelete;
	id = _other.id;
	lifeSpan = _other.lifeSpan;
	name = _other.name;
	displayName = _other.displayName;

	for (const pair<type_index, Component*>& _pair : components)
	{
		//CreateComponent<CameraComponent>(*_pair.second);
		//CreateComponent<TYPE(_pair.first)>(*_pair.second);
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
	for (const pair<type_index, Component*>& _pair : components)
	{
		delete _pair.second;
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

	for (const pair<type_index, Component*>& _pair : components)
	{
		_pair.second->BeginPlay();
	}
}

void Actor::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	for (const pair<type_index, Component*>& _pair : components)
	{
		_pair.second->Tick(_deltaTime);
	}
}

void Actor::BeginDestroy()
{
	for (const pair<type_index, Component*>& _pair : components)
	{
		_pair.second->BeginDestroy();
	}
}


void Actor::SetName(const string& _name)
{
	if (name == _name) return;
	name = _name;
	displayName = level->GetActorManager().GetDisplayName(this);
}

void Actor::CreateSocket(const string& _name, const TransformData& _transform, const AttachmentType& _type)
{
	Actor* _socket = level->SpawnActor<Actor>(_name, _transform);
	AddChild(_socket, _type);
}

void Actor::Destroy()
{
	SetToDelete();
}

void Actor::AddComponent(const type_index& _type, Component* _component)
{
	components.insert({ _type, _component });
}

void Actor::RemoveComponent(Component* _component)
{
	components.erase(TYPE_ID(_component));
}