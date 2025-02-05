#pragma once
#include "Singleton.h"
#include "Sample.h"
#include "SoundSample.h"

enum AudioExtensionType
{
	MP3,
	WAV
};

class AudioManager : public Singleton<AudioManager>
{
	bool isMuted;
	float volume;
	multimap<string, Sample*> allSamples;

public: 
	FORCEINLINE void RegisterSample(Sample* _sample)
	{
		allSamples.insert(make_pair(_sample->GetPath(), _sample));
	}
	FORCEINLINE string GetExtension(const AudioExtensionType& _type)
	{
		return vector<string>({ ".mp3", ".wav" })[_type];
	}

public:
	AudioManager();
	~AudioManager();

	template <typename Type, IS_BASE_OF(Sample, Type)>
	Type* PlaySample(const string& _path, const AudioExtensionType& _type = MP3, const Time& _time = Time())
	{
		//static_assert(is_base_of_v<Sample, T>, "ERREUR CUSTOM !");

		const string& _finalPath = _path + GetExtension(_type);

		using Iterator = multimap<string, Sample*>::iterator;
		const pair<Iterator, Iterator>& _activeSamples = allSamples.equal_range(_finalPath);
		Sample* _sample;

		for (Iterator _iterator = _activeSamples.first; _iterator != _activeSamples.second; ++_iterator)
		{
			_sample = _iterator->second;
			if (_sample->IsAvailable())
			{
				_sample->Play(_time);
				return Cast<Type>(_sample);
			}
		}

		_sample = new Type(_finalPath);
		_sample->Play(_time);

		return Cast<Type>(_sample);
	}
	void ToggleMute();
};