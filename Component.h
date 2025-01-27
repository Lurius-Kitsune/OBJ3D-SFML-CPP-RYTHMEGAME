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
	virtual ~Component() = default;

public:
	virtual void BeginPlay() override {};
	virtual void Tick(const float _deltaTime) override {};
	virtual void BeginDestroy() override {};
};