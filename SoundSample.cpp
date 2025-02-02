#include "SoundSample.h"
#include "AudioManager.h"
#include "TimerManager.h"

SoundSample::SoundSample(const string& _path) : Sample(_path)
{

	if (!buffer.loadFromFile(_path))
	{
		LOG(Error, "Invalid path : " + _path);
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


void SoundSample::Play(const Time& _time, const Time& _duration)
{
	if (!sound) return;
	Super::Play(_time);
	if (_duration != Time())
	{
		new Timer([&]() {sound->stop(); }, _duration, true, false);
	}
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