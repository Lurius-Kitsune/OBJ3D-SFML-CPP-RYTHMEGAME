#pragma once
#include "CoreMinimal.h"
#include "ActorManager.h"
#include "CameraManager.h"
#include "AudioManager.h"
#include "GameMode.h"
#include "Widget.h"

using namespace Camera;
using namespace UI;

class Level
{
	bool isLoaded;
	string name;
	ActorManager actorManager;
	CameraManager cameraManager;
	AudioManager audioManager;
	GameMode* gameMode;

protected:
	RenderWindow window;
	SubclassOf<GameMode> gameModeRef;

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
	FORCEINLINE AudioManager& GetAudioManager()
	{
		return audioManager;
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
		return Cast<Type>(GetGameMode()->GetHUD());
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
	FORCEINLINE Type* SpawnWidget(const SubclassOf<Widget> _widgetRef)
	{
		Type* _widget = SpawnActor<Type>(_widgetRef);
		GetHUD()->RegisterWidget(_widget);
		return _widget;
	}

	#pragma endregion

	#pragma region SpawnSample

	template <typename Type = Sample, typename ...Args, IS_BASE_OF(Sample, Type)>
	FORCEINLINE Type* SpawnSample(const string& _path, const AudioExtensionType& _type = MP3,
								  const Time& _time = Time(), const Time& _duration = Time())
	{
		const string& _finalPath = _path + audioManager.GetExtension(_type);
		Sample* _sample = audioManager.GetAvailable(_finalPath);

		if (_sample)
		{
			audioManager.PlaySample(_sample);
			return _sample;
		}

		_sample = SpawnActor<Type>(_finalPath);
		audioManager.RegisterSample(_sample);
		return _sample;
	}

	/*template <typename Type = Sample, IS_BASE_OF(Sample, Type)>
	FORCEINLINE Type* SpawnSample(const SubclassOf<Sample> _sampleRef)
	{
		Type* _sample = SpawnActor<Type>(_sampleRef);
		audioManager.RegisterSample(_sample);
		const Sample& _objectRef = _sampleRef.GetObject();
		audioManager.PlaySample(_sample, _objectRef.time, _objectRef.duration);
		return _sample;
	}*/

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