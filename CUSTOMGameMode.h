#pragma once
#include "GameMode.h"
#include "CUSTOMPlayerController.h"
#include "CUSTOMHUD.h"

class CUSTOMGameMode : public GameMode
{
public:
	FORCEINLINE virtual CUSTOMPlayerController* GetPlayerControllerRef() override
	{
		return new CUSTOMPlayerController(GetLevel());
	}
	FORCEINLINE virtual CUSTOMHUD* GetHUDRef() override
	{
		return new CUSTOMHUD(GetLevel());
	}
public:
	CUSTOMGameMode(Level* _level, const string& _name = "GameMode");
	CUSTOMGameMode(const CUSTOMGameMode& _other);
};