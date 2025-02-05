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
		if (currentLevel) currentLevel->OnUnload();
		currentLevel = _level;
		if (currentLevel) currentLevel->BeginPlay(); // Le if est au cas où le level a été mis en nullptr
	}
	FORCEINLINE bool SetLevel(const string& _name)
	{
		if (!allLevels.contains(_name))
		{
			LOG(Error, "Level \"" + _name + "\" not found");
			return false;
		}

		SetLevel(allLevels[_name]);

		return true;
	}

	FORCEINLINE void RegisterLevel(const string& _name, Level* _level)
	{
		allLevels.emplace(_name, _level);
	}

	FORCEINLINE void Destroy()
	{
		for (auto _it = allLevels.begin(); _it != allLevels.end(); _it++)
		{
			_it->second->BeginDestroy();
 			delete _it->second;
		}
		allLevels.clear();
	}
};

