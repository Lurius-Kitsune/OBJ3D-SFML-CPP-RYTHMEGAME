#pragma once
#include "CoreMinimal.h"
#include "ActorManager.h"
#include "CameraManager.h"
#include "GameMode.h"
#include "Widget.h"

using namespace Camera;
using namespace UI;

class Level
{
	bool isLoaded;

protected:
	RenderWindow window;
	string name;
	ActorManager actorManager;
	CameraManager cameraManager;
	SubclassOf<GameMode> gameModeRef;
	GameMode* gameMode;

public:
	#pragma region Window

	FORCEINLINE bool IsActive() const
	{
		return window.isOpen();
	}
	FORCEINLINE RenderWindow& GetRenderWindow()
	{
		return window;
	}
	FORCEINLINE Vector2f GetWindowSize() const
	{
		return CAST(Vector2f, window.getSize());
	}

	#pragma endregion

	FORCEINLINE string GetName() const
	{
		return name;
	}
	FORCEINLINE ActorManager& GetActorManager()
	{
		return actorManager;
	}
	FORCEINLINE CameraManager& GetCameraManager()
	{
		return cameraManager;
	}
	FORCEINLINE GameMode* GetGameMode()
	{
		if (!gameMode)
		{
			gameMode = SpawnActor<GameMode>(gameModeRef);
		}

		return gameMode;
	}
	template <typename Type = UI::HUD, IS_BASE_OF(Type, UI::HUD)>
	FORCEINLINE Type* GetHUD()
	{
		return Cast<Type>(gameMode->GetHUD());
	}

	#pragma region Spawn

	#pragma region SpawnActor

	template <typename Type = Actor, typename ...Args, IS_BASE_OF(Actor, Type)>
	FORCEINLINE Type* SpawnActor(Args&&... _args)
	{
		Type* _actor = new Type(this, forward<Args>(_args)...);
		_actor->Construct();
		return _actor;
	}

	template <typename Type = Actor, typename ...Args, IS_BASE_OF(Actor, Type)>
	FORCEINLINE Type* SpawnActor(const SubclassOf<Type> _actorRef)
	{
		Type* _actor = new Type(_actorRef.GetObject());
		_actor->Construct();
		return _actor;
	}

	#pragma endregion

	#pragma region SpawnCamera

	template <typename Type = CameraActor, typename ...Args, IS_BASE_OF(CameraActor, Type)>
	FORCEINLINE Type* SpawnCamera(Args&&... _args)
	{
		Type* _camera = SpawnActor<Type>(forward<Args>(_args)...);
		cameraManager.AddCamera(_camera);
		return _camera;
	}

	template <typename Type = CameraActor, IS_BASE_OF(CameraActor, Type)>
	FORCEINLINE Type* SpawnCamera(const SubclassOf<Type> _actorRef)
	{
		Type* _camera = SpawnActor<Type>(_actorRef);
		cameraManager.AddCamera(_camera);
		return _camera;
	}

	#pragma endregion

	#pragma region SpawnWidget

	template <typename Type = Widget, typename ...Args, IS_BASE_OF(Widget, Type)>
	FORCEINLINE Type* SpawnWidget(Args&&... _args)
	{
		Type* _widget = SpawnActor<Type>(forward<Args>(_args)...);
		GetHUD()->RegisterWidget(_widget);
		return _widget;
	}

	template <typename Type = Widget, IS_BASE_OF(Widget, Type)>
	FORCEINLINE Widget* SpawnWidget(const SubclassOf<Widget> _widgetRef)
	{
		Type* _widget = SpawnActor<Type>(_widgetRef);
		GetHUD()->RegisterWidget(_widget);
		return _widget;
	}

	#pragma endregion

	#pragma endregion

public:
	Level(const string& _name);

public:
	void Update(const float _deltaTime);
	void UpdateWindow();
	virtual void Load();
	virtual void Unload();

protected:
	virtual void InitLevel();
};