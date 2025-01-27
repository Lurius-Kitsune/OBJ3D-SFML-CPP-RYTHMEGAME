#include "AudioManager.h"

AudioManager::AudioManager()
{
	isMuted = false;
	volume = 100.0f;
	allSamples = multimap<string, Sample*>();
}

AudioManager::~AudioManager()
{
	for (pair<string, Sample*> _samplePair : allSamples)
	{
		delete _samplePair.second;
	}
}


void AudioManager::ToggleMute()
{
	isMuted = !isMuted;

	for (pair<string, Sample*> _samplePair : allSamples)
	{
		_samplePair.second->SetMuteStatus(isMuted);
	}
}