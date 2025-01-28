#pragma once
#include "Level.h"

class BeatMapLevel : public Level
{
	vector<BeatMap*> beatMapCollection;
	BeatMapPathList listOfPaths;

public:
	BeatMapLevel();
	~BeatMapLevel();

	FORCEINLINE BeatMap* GetBeatMap(int _number)
	{
		return beatMapCollection.at(_number);
	}

	FORCEINLINE int GetBeatMapCollectionSize()
	{
		return static_cast<int>(beatMapCollection.size());
	}

	FORCEINLINE string GetBeatMapDifficulty(int _number)
	{
		return beatMapCollection.at(_number)->GetDifficulty();
	}

private:

};




