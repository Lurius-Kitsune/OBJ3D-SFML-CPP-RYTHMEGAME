#include "CameraManager.h"

Camera::CameraManager::CameraManager()
{
	allRendersData = map<u_int, RenderData>();
	allCameras = map<string, CameraActor*>();
	current = nullptr;
}


void Camera::CameraManager::RenderAllCameras(RenderWindow& _window)
{
	vector<RenderData> _renderWidgets;
	bool _isFirst = true;

	int _index = -1;
	for (const pair<int, u_int>& _element : allElements)
	{
		if (_element.first == _index) continue;

		_index = _element.first;
		using Iterator = multimap<int, u_int>::iterator;
		const pair<Iterator, Iterator>& _results = allElements.equal_range(_index);

		// Pour chaque caméra
		for (const pair<string, CameraActor*>& _pair : allCameras)
		{
			// Je définis la vue
			_window.setView(*_pair.second->GetView());

			// Je draw tous les éléments
			for (Iterator _it = _results.first; _it != _results.second; ++_it)
			{
				const RenderData& _data = allRendersData.at(_it->second);

				// Si il s'agit d'un widget
				if (_isFirst && _data.type == Screen)
				{
					// Je l'ajoute comme à afficher plus tard
					_renderWidgets.push_back(_data);
					continue;
				}

				// Je draw l'élément
				_data.callback(_window);
			}

			_isFirst = false;
		}
	}

	// Je définis la vue
	_window.setView(_window.getDefaultView());

	for (const RenderData& _data : _renderWidgets)
	{
		// Je draw l'élément
		_data.callback(_window);
	}
}

void Camera::CameraManager::UnbindOnRenderWindow(const u_int& _uniqueId)
{
	if (!allRendersData.contains(_uniqueId)) return;

	const int _zOrder = allRendersData.at(_uniqueId).zOrder;
	using Iterator = multimap<int, u_int>::iterator;
	const pair<Iterator, Iterator>& _results = allElements.equal_range(_zOrder);

	for (Iterator _it = _results.first; _it != _results.second; ++_it)
	{
		if (_it->second != _uniqueId) continue;
		allElements.erase(_it);
		break;
	}

	allRendersData.erase(_uniqueId);
}
