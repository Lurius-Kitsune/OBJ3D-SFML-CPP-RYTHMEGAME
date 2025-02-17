#pragma once
#include "CameraActor.h"
#include "RenderType.h"

namespace Camera
{
	struct RenderData
	{
		RenderType type;
		using RenderCallback = function<void(RenderWindow&)>;
		RenderCallback callback;
		int zOrder;

		RenderData(const RenderCallback& _callback, const RenderType& _type = World)
		{
			callback = _callback;
			type = _type;
			zOrder = 0;
		}
	};

	class CameraManager
	{
		using AllCameras = unordered_map<string, CameraComponent*>;
		using Iterator = multimap<int, u_int>::iterator;
		using RenderWidgets = vector<Camera::RenderData>;

		multimap<int, u_int> allElements;
		map<u_int, RenderData> allRendersData;
		AllCameras allCameras;
		CameraComponent* current;

	public:
		FORCEINLINE void Register(CameraComponent* _camera)
		{
			if (!_camera) return;

			allCameras.insert({ _camera->GetOwner()->GetDisplayName(), _camera });
			SetCurrent(_camera);
		}
		FORCEINLINE void Unregister(const string& _displayName)
		{
			if (!allCameras.contains(_displayName)) return;

			allCameras.erase(_displayName);
			SetPreviousCurrent();
		}
		FORCEINLINE void Unregister(CameraComponent* _camera)
		{
			if (!_camera) return;

			allCameras.erase(_camera->GetOwner()->GetDisplayName());
			SetPreviousCurrent();
		}
		FORCEINLINE void SetZOrder(const u_int& _uniqueId, const int _zOrder)
		{
			if (!allRendersData.contains(_uniqueId)) return;
			const pair<Iterator, Iterator>& _results = allElements.equal_range(allRendersData.at(_uniqueId).zOrder);
			for (Iterator _it = _results.first; _it != _results.second; ++_it)
			{
				if (_it->second == _uniqueId)
				{
					allElements.erase(_it);
					break;
				}
			}
			allRendersData.at(_uniqueId).zOrder = _zOrder;
			allElements.insert({ _zOrder, _uniqueId });
		}
		FORCEINLINE void SetCurrent(CameraComponent* _camera)
		{
			if (!_camera) return;
			current = _camera;
		}
		FORCEINLINE void SetPreviousCurrent()
		{
			if (allCameras.empty())
			{
				LOG(Fatal, "There is no more camera to render !");
				return;
			}

			using Iterator = AllCameras::iterator;
			Iterator _end = allCameras.end();
			const Iterator& _previous = _end--;
			SetCurrent(_previous->second);
		}
		FORCEINLINE u_int BindOnRenderWindow(RenderData _data, const int _zOrder = 0)
		{
			const u_int& _id = GetUniqueID();
			_data.zOrder = _zOrder;
			allRendersData.insert({ _id, _data });
			allElements.insert({ _zOrder, _id });
			return _id;
		}
		FORCEINLINE CameraComponent* GetCurrent() const
		{
			return current;
		}
		FORCEINLINE CameraComponent* GetCameraByName(const string& _name) const
		{
			if (!allCameras.contains(_name)) return nullptr;
			return allCameras.at(_name);
		}

	public:
		CameraManager();

		void Render(RenderWindow& _window, const bool _isSplitScreen);
		bool SetRenderView(CameraComponent* _camera, RenderWindow& _window);
		void RenderAllCameras(RenderWindow& _window, const int _index, const AllCameras& _allCameras);
		void RenderAllElements(RenderWindow& _window, const pair<Iterator, Iterator>& _results, bool& _isFirst, RenderWidgets& _renderWidgets);
		void RenderAllWidgets(RenderWindow& _window, const vector<RenderData>& _renderWidgets);
		void UnbindOnRenderWindow(const u_int& _uniqueId);
	};
}