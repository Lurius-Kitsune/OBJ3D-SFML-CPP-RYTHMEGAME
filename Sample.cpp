#include "Sample.h"

Sample::Sample(const string& _path)
{
	volume = 50.0f;
	path = _path;
}


void Sample::Play(const Time& _time)
{
	if (IsStatusByIndex(1))
	{
		Stop();
	}

	SetVolume(volume);
}