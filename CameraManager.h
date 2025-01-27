#pragma once
#include "Singleton.h"
#include "CameraActor.h"
#include "Level.h"

class CameraManager : public Singleton<CameraManager>
{
	using OnRenderWindow = function<void(RenderWindow&)>;
	map<u_int, OnRenderWindow> onRenderWindow;
	map<string, CameraActor*> allCameras;
	CameraActor* current;

public:
	FORCEINLINE u_int BindOnRenderWindow(OnRenderWindow _callback)
	{
		u_int _id = GetUniqueID();
		onRenderWindow.insert({ _id, _callback });
		return _id;
	}
	FORCEINLINE void UnbindOnRenderWindow(const u_int& _uniqueId)
	{
		onRenderWindow.erase(_uniqueId);
	}
	FORCEINLINE void SetCurrent(CameraActor* _camera)
	{
		if (!_camera) return;
		current = _camera;
	}
	FORCEINLINE CameraActor* GetCurrent() const
	{
		return current;
	}
	FORCEINLINE CameraActor* GetCameraByName(const string& _name) const
	{
		if (!allCameras.contains(_name)) return nullptr;
		return allCameras.at(_name);
	}
private:
	FORCEINLINE void Register(CameraActor* _camera)
	{
		if (!_camera) return;
		allCameras.insert({ _camera->GetName(), _camera });
		//allCameras.insert({ _camera->GetDisplayName(), _camera });
	}

public:
	CameraManager();

	void RenderAllCameras(RenderWindow& _window);

	template <typename Type = CameraActor, IS_BASE_OF(CameraActor, Type)>
	Type* CreateCamera(const string& _name = "Camera")
	{
		Type* _camera = Level::SpawnActor(Type(_name));
		Register(_camera);

		if (!current)
		{
			SetCurrent(_camera);
		}

		return _camera;
	}
};