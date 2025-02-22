#pragma once
#include "Core.h"

class Component : public Core
{
protected:
	class Actor* owner;

public:
	FORCEINLINE Actor* GetOwner() const
	{
		return owner;
	}

public:
	Component(Actor* _owner);
	Component(Actor* _owner, const Component& _other);
	virtual ~Component() = default;

public:
	virtual void Construct() override;
	virtual void Deconstruct() override;
	virtual void BeginPlay() override {};
	virtual void Tick(const float _deltaTime) override {};
	virtual void BeginDestroy() override {};

	virtual Component* Clone(Actor* _owner) const = 0;
};