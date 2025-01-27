#pragma once
#include "Sample.h"

class MusicSample : public Sample
{
	using MusicStatus = Music::Status;

	Music* music;

	#pragma region Sample

	FORCEINLINE virtual void UpdateVolume(const float _volume) override
	{
		music->setVolume(_volume);
	}
	FORCEINLINE virtual int GetStatus() const override
	{
		return CAST(int, music->getStatus());
	}
public:
	FORCEINLINE virtual bool IsAvailable() const override
	{
		return CAST(MusicStatus, GetStatus()) != MusicStatus::Playing;
	}
	FORCEINLINE virtual void SetLoop(const bool _isLoop) override
	{
		music->setLooping(_isLoop);
	}
	FORCEINLINE virtual bool AddPitch(const float _pitchOffset) override
	{
		float _newPitch = music->getPitch() + _pitchOffset;
		if (_newPitch > 2.0f || _newPitch < 0.0f) return false;

		music->setPitch(_newPitch);
		return true;
	}


	#pragma endregion

public:
	FORCEINLINE float GetVolume() const
	{
		return music->getVolume();
	}

public:
	MusicSample(const string& _path);
	~MusicSample();

	virtual void Play(const Time& _time = Time()) override;
	virtual void Pause() override;
	virtual void Stop() override;
};