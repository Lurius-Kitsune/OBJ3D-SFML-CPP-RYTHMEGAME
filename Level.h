#pragma once
#include "CoreMinimal.h"
#include "ActorManager.h"
#include "CameraManager.h"
#include "GameMode.h"

using namespace Camera;

class Level : public Core
{
	RenderWindow window;

protected:
	string name;
	ActorManager actorManager;
	CameraManager cameraManager;
	GameMode* gamemode;

public:

	#pragma region Actors
	template <typename T = Actor>
	FORCEINLINE T* SpawnActor()
	{
		const SubclassOf<T>& _ref = SubclassOf(T());
		return SpawnActor(_ref);
	}

	template <typename T = Actor>
	FORCEINLINE T* SpawnActor(const SubclassOf<T>& _ref)
	{
		T* _actor = new T(_ref.GetObject());
		_actor->SetLevelReference(this);
		_actor->Construct();
		return _actor;
	}

	template <typename T = Actor>
	FORCEINLINE T* SpawnActor(const T& _ref)
	{
		T* _actor = new T(_ref);
		_actor->SetLevelReference(this);
		_actor->Construct();
		return _actor;
	}

	FORCEINLINE ActorManager& GetActorManager()
	{
		return actorManager;
	}
#pragma endregion

	#pragma region Cameras
	FORCEINLINE CameraManager& GetCameraManager()
	{
		return cameraManager;
	}

	template <typename Type = CameraActor, typename ...Args, IS_BASE_OF(CameraActor, Type)>
	FORCEINLINE Type* CreateCamera(Args... _args)
	{
		Type* _camera = SpawnActor(Type(_args...));
		return cameraManager.AddCamera(_camera);
	}

#pragma endregion

	#pragma region Window

	FORCEINLINE RenderWindow& GetRenderWindow()
	{
		return window;
	}

	FORCEINLINE Vector2f GetWindowSize() const
	{
		return CAST(Vector2f, window.getSize());
	}

#pragma endregion

public:
	Level(const string& _name, GameMode* _gamemode);
	virtual ~Level();

public:
	virtual void Tick(const float _deltaTime) override;
	virtual void BeginPlay() override;
	virtual void OnUnload();
	virtual void BeginDestroy() override;

	void UpdateWindow();

private:
	virtual void SetActive(const bool _active) override;
	virtual void InitLevel();
	// TODO move to PlayerController
	//static void SetViewTarget()
};