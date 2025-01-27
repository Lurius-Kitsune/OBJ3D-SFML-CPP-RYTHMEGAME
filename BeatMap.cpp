#include "BeatMap.h"

BeatMap::BeatMap(const int _missDamage, const float _timeStamp)
{
	MissDamage = _missDamage;
	timeStamp = nullptr;
}

BeatMap::BeatMap(const string& _path)
{

}

BeatMap::~BeatMap()
{
}

void BeatMap::Start()
{
	timeStamp = new Time();
}
