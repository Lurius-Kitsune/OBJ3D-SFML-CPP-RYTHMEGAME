#pragma once
#include "CoreMinimal.h"

class Core
{
	bool isActive = false;

public:
	FORCEINLINE void SetActive(const bool _active)
	{
		isActive = _active;
	}
	FORCEINLINE bool IsActive() const
	{
		return isActive;
	}

public:
	virtual void BeginPlay() = 0;
	virtual void Tick(const float _deltaTime);
	virtual void BeginDestroy() = 0;
};