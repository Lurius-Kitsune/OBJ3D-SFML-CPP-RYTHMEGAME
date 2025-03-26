#pragma once
#include "Actor.h"
#include "PlayerController.h"
#include "HUD.h"

class Pawn;
using namespace UI;

class GameMode : public Actor
{
protected:
	PlayerController* controller;
	HUD* hud;
	bool isSplitScreen;

public:
	#pragma region PlayerController

	template<typename Type = PlayerController, IS_BASE_OF(PlayerController, Type)>
	FORCEINLINE Type* GetPlayerController()
	{
		if (!controller)
		{
			Type* _type = SpawnPlayerController<Type>();
			controller = _type;
			return _type;
		}

		return Cast<Type>(controller);
	}

	template<typename Type = PlayerController, IS_BASE_OF(PlayerController, Type)>
	FORCEINLINE Type* SpawnPlayerController()
	{
		PlayerController* _playerController = GetPlayerControllerRef();
		const SubclassOf<Type>& _controllerRef = *Cast<Type>(_playerController);

		Type* _type = Spawn<Type>(_controllerRef);
		_type->Construct();
		_type->Register();

		delete _playerController;
		return _type;
	}

	FORCEINLINE virtual PlayerController* GetPlayerControllerRef()
	{
		return new PlayerController(GetLevel());
	}

	#pragma endregion

	#pragma region HUD

	template<typename Type = HUD, IS_BASE_OF(HUD, Type)>
	FORCEINLINE Type* GetHUD()
	{
		if (!hud)
		{
			Type* _type = SpawnHUD<Type>();
			hud = _type;
			return _type;
		}

		return Cast<Type>(hud);
	}

	template<typename Type, IS_BASE_OF(HUD, Type)>
	FORCEINLINE Type* SpawnHUD()
	{
		HUD* _hud = GetHUDRef();
		const SubclassOf<Type>& _hudRef = *Cast<Type>(_hud);

		Type* _type = Spawn<Type>(_hudRef);
		_type->Construct();
		_type->Register();

		delete _hud;
		return _type;
	}

	FORCEINLINE virtual HUD* GetHUDRef()
	{
		return new HUD(GetLevel());
	}

	#pragma endregion

	#pragma region SplitScreen
	FORCEINLINE void SetIsSplitScreen(const bool _isSplitScreen)
	{
		isSplitScreen = _isSplitScreen;
	}
	FORCEINLINE bool IsSplitScreen() const
	{
		return isSplitScreen;
	}
	#pragma endregion

public:
	GameMode(Level* _level, const string& _name = "GameMode");
	GameMode(const GameMode& _other);

public:
	void Possess(Pawn* _pawn);
	void Unpossess(Pawn* _pawn);
};