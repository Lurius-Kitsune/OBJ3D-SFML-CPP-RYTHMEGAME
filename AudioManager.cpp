#include "AudioManager.h"

AudioManager::AudioManager()
{
	isMuted = false;
	volume = 100.0f;
	allSamples = multimap<string, Sample*>();
}


void AudioManager::ToggleMute()
{
	isMuted = !isMuted;

	for (pair<string, Sample*> _samplePair : allSamples)
	{
		_samplePair.second->SetMuteStatus(isMuted);
	}
}

void AudioManager::PlaySample(Sample* _sample, const Time& _time, const Time& _duration)
{
	if (!_sample) return;
	_sample->Play(_time, _duration);
}