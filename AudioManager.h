#pragma once
#include "Sample.h"
#include "SoundSample.h"

enum AudioExtensionType
{
	MP3,
	WAV
};

class AudioManager
{
	bool isMuted;
	float volume;
	multimap<string, Sample*> allSamples;

public: 
	FORCEINLINE void RegisterSample(Sample* _sample)
	{
		allSamples.insert(make_pair(_sample->GetPath(), _sample));
	}
	FORCEINLINE Sample* GetAvailable(const string& _finalPath)
	{
		using Iterator = multimap<string, Sample*>::iterator;
		const pair<Iterator, Iterator>& _activeSamples = allSamples.equal_range(_finalPath);

		for (Iterator _iterator = _activeSamples.first; _iterator != _activeSamples.second; ++_iterator)
		{
			Sample* _sample = _iterator->second;
			if (_sample->IsAvailable()) return _sample;
		}

		return nullptr;
	}
	FORCEINLINE string GetExtension(const AudioExtensionType& _type) const
	{
		return vector<string>({ ".mp3", ".wav" })[_type];
	}

public:
	AudioManager();

	void ToggleMute();
	void PlaySample(Sample* _sample, const Time& _time = Time(), const Time& _duration = Time());
};