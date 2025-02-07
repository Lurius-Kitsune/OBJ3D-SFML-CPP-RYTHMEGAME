#include "Sample.h"

Sample::Sample(Level* _level, const string& _path) : Actor(_level)
{
	volume = 50.0f;
	path = _path;
}


void Sample::Play(const Time& _time, const Time& _duration)
{
	if (IsStatusByIndex(1))
	{
		Stop();
	}

	SetVolume(volume);
}