#include "SoundSample.h"
#include "AudioManager.h"
#include "TimerManager.h"

SoundSample::SoundSample(Level* _level, const string& _path) : Sample(_level, _path)
{
	const string& _finalPath = "Assets/Sounds/" + _path;

	if (!buffer.loadFromFile(_finalPath))
	{
		LOG(Error, "Invalid path : " + _finalPath);
		sound = nullptr;
		return;
	}

	sound = new Sound(buffer);
}

SoundSample::~SoundSample()
{
	delete sound;
}


void SoundSample::Play(const Time& _time, const Time& _duration)
{
	if (!sound) return;

	Super::Play(_time);
	sound->play();
	sound->setPlayingOffset(_time);

	if (_duration != Time())
	{
		new Timer([&]() { sound->stop(); }, seconds(_duration.asSeconds()), true, false);
	}
}

void SoundSample::Pause()
{
	if (!sound) return;
	sound->pause();
}

void SoundSample::Stop()
{
	if (!sound) return;
	sound->stop();
}