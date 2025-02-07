#pragma once
#include "CoreMinimal.h"
#include "ActorManager.h"
#include "CameraManager.h"
#include "GameMode.h"

using namespace Camera;

class Level
{
	bool isLoaded;
	RenderWindow window;

protected:
	string name;
	ActorManager actorManager;
	CameraManager cameraManager;
	SubclassOf<GameMode> gamemodeRef;
	GameMode* gamemode;

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
		if (!gamemode)
		{
			gamemode = SpawnActor<GameMode>(gamemodeRef);
		}

		return gamemode;
	}

	#pragma region SpawnActor

	template <typename Type = Actor, typename ...Args, IS_BASE_OF(Actor, Type)>
	FORCEINLINE Type* SpawnActor(Args&&... _args)
	{
		Type* _actor = new Type(forward<Args>(_args)...);
		_actor->SetLevelReference(this);

		if constexpr (SAME_VALUE(TYPE(_actor), CameraActor))
		{
			cameraManager.AddCamera(_actor);
		}

		_actor->Construct();
		return _actor;
	}
	template <typename Type = Actor, typename ...Args, IS_BASE_OF(Actor, Type)>
	FORCEINLINE Type* SpawnActor(const SubclassOf<Type> _actorRef)
	{
		Type* _actor = new Type(_actorRef.GetObject());
		_actor->SetLevelReference(this);
		_actor->Construct();
		return _actor;
	}
	template <typename Type = Actor, typename ...Args, IS_BASE_OF(CameraActor, Type)>
	FORCEINLINE Type* SpawnCamera(const SubclassOf<Type> _actorRef)
	{
		Type* _actor = SpawnActor(_actorRef);
		cameraManager.AddCamera(_actor);
		return _actor;
	}


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