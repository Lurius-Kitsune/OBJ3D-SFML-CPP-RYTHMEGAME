#pragma once
#include "Singleton.h"
#include "Level.h"

class LevelManager : public Singleton<LevelManager>
{
	map<string, Level*> allLevels;
	Level* currentLevel;

public:
	FORCEINLINE Level* GetCurrentLevel() const
	{
		return currentLevel;
	}
	FORCEINLINE void SetLevel(Level* _level)
	{
		if (currentLevel) currentLevel->Unload();
		currentLevel = _level;
		if (currentLevel) currentLevel->Load();
	}
	FORCEINLINE bool SetLevel(const string& _name)
	{
		if (!allLevels.contains(_name))
		{
			LOG(Error, "Level \"" + _name + "\" not found !");
			return false;
		}

		SetLevel(allLevels[_name]);
		return true;
	}
	FORCEINLINE void RegisterLevel(const string& _name, Level* _level)
	{
		allLevels.emplace(_name, _level);
	}
	FORCEINLINE void UnregisterLevel(const string& _name)
	{
		allLevels.erase(_name);
	}
	FORCEINLINE void Destroy()
	{
		for (auto _it = allLevels.begin(); _it != allLevels.end(); ++_it)
		{
			_it->second->Unload();
 			delete _it->second;
		}

		allLevels.clear();
	}

public:
	LevelManager() = default;
};