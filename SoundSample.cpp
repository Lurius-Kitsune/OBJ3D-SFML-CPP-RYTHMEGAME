#include "SoundSample.h"
#include "AudioManager.h"

SoundSample::SoundSample(const string& _path) : Sample(_path)
{
	const string& _finalPath = "Assets/Sounds/" + _path;

	if (!buffer.loadFromFile(_finalPath))
	{
		LOG(Error, "Invalid path : " + _finalPath);
		sound = nullptr;
		return;
	}

	sound = new Sound(buffer);
	M_AUDIO.RegisterSample(this);
}

SoundSample::~SoundSample()
{
	delete sound;
}


void SoundSample::Play(const Time& _time)
{
	if (!sound) return;

	Super::Play(_time);
	sound->play();
	sound->setPlayingOffset(_time);
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