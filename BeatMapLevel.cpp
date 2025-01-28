#include "BeatMapLevel.h"

BeatMapLevel::BeatMapLevel()
{
	listOfPaths = BeatMapPathList();
	for (size_t _index = 0; _index < listOfPaths.pathList.size(); _index++)
	{
		beatMapCollection.push_back(new BeatMap(listOfPaths.pathList.at(_index)));
		beatMapCollection.at(_index)->LoadBeatMap();
	}
}

BeatMapLevel::~BeatMapLevel()
{
	beatMapCollection.clear();
}