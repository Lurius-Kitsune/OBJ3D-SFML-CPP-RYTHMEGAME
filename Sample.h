#pragma once
#include "CoreMinimal.h"

class Sample
{
	float volume;
	string path;

	FORCEINLINE virtual void UpdateVolume(const float _volume) = 0;
	FORCEINLINE virtual int GetStatus() const = 0;
	FORCEINLINE virtual bool IsStatusByIndex(const u_int& _statusIndex) const
	{
		return GetStatus() == _statusIndex;
	}
public:
	FORCEINLINE virtual bool IsAvailable() const = 0;
	FORCEINLINE virtual void SetLoop(const bool _isLoop) = 0;
	FORCEINLINE virtual bool AddPitch(const float _pitch) = 0;

	FORCEINLINE void SetMuteStatus(const bool _status)
	{
		UpdateVolume(_status ? 0.0f : volume);
	}
	FORCEINLINE void SetVolume(const float _volume)
	{
		UpdateVolume(volume = _volume);
	}
	FORCEINLINE float GetVolume() const
	{
		return volume;
	}
	FORCEINLINE string GetPath() const
	{
		return path;
	}
	
public:
	Sample(const string& _path);
	virtual ~Sample() = default;

public:
	virtual void Play(const Time& _time = Time());
	virtual void Pause() = 0;
	virtual void Stop() = 0;
};