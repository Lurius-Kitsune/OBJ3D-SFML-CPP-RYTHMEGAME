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
	zOrder = 0;
	displayName = "Unknown";
	components = set<Component*>();
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
	zOrder = _other.zOrder;
	for (Component* _component : _other.components)
	{
		AddComponent(_component->Clone(this));
	}

	root = GetComponent<RootComponent>();
	parent = _other.parent;
	attachment = _other.attachment;
	for (Actor* _child : _other.children)
	{
		children.insert(new Actor(*_child));
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

	for (Component* _component : components)
	{
		_component->Construct();
	}
 }

void Actor::Deconstruct()
{
	for (Component* _component : components)
	{
		_component->Deconstruct();
	}

	SetActive(false);
	Unregister();
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


void Actor::Register()
{
	level->GetActorManager().AddActor(this);
}

void Actor::Unregister()
{
	level->GetActorManager().RemoveActor(this);
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

void Actor::AddComponent(Component* _component)
{
	components.insert(_component);
}

void Actor::RemoveComponent(Component* _component)
{
	components.erase(components.find(_component));
}