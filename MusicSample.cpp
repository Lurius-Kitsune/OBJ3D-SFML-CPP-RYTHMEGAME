#include "MusicSample.h"
#include "AudioManager.h"

MusicSample::MusicSample(const string& _path) : Sample(_path)
{
	const string& _finalPath = "Assets/Musics/" + _path;
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


void MusicSample::Play(const Time& _time)
{
	if (!music) return;

	Super::Play(_time);
	music->play();
	music->setPlayingOffset(_time);
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