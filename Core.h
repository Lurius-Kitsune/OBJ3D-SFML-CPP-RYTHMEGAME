#pragma once
#include "CoreMinimal.h"

class Core
{
	bool isActive = false;

public:
	FORCEINLINE bool IsActive() const
	{
		return isActive;
	}

	virtual FORCEINLINE void SetActive(const bool _active)
	{
		isActive = _active;
	}

public:
	virtual void BeginPlay() = 0;
	virtual void Tick(const float _deltaTime);
	virtual void BeginDestroy() = 0;
};