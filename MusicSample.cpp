#include "MusicSample.h"
#include "AudioManager.h"
#include "TimerManager.h"

MusicSample::MusicSample(const string& _path) : Sample(_path)
{
	const string& _finalPath = _path;
	music = new Music();

	if (!music->openFromFile(_finalPath))
	{
		LOG(Error, "Invalid path : " + _finalPath);
		delete music;
		music = nullptr;
		return;
	}

	M_AUDIO.RegisterSample(this);
}

MusicSample::~MusicSample()
{
	delete music;
}


void MusicSample::Play(const Time& _offset, const Time& _duration)
{
	if (!music) return;
	Super::Play(_offset);
	music->play();
	music->setPlayingOffset(_offset);
	if (_duration != Time())
	{
		new Timer([&]() {music->stop(); }, seconds(_duration.asSeconds()), true, false);
	}
}

void MusicSample::Pause()
{
	if (!music) return;
	music->pause();
}

void MusicSample::Stop()
{
	if (!music) return;
	music->stop();
}