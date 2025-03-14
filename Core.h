#pragma once
#include "CoreMinimal.h"

class Core
{
	bool isActive = false;

public:
	FORCEINLINE virtual void SetActive(const bool _active)
	{
		isActive = _active;
	}
	FORCEINLINE bool IsActive() const
	{
		return isActive;
	}

public:
	virtual void Construct() = 0;
	virtual void Deconstruct() = 0;
	virtual void BeginPlay() = 0;
	virtual void Tick(const float _deltaTime) = 0;
	virtual void BeginDestroy() = 0;
};