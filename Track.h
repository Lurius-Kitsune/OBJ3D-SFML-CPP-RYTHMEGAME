#pragma once
#include "CoreMinimal.h"
#include "BeatMap.h"
#include "MusicSample.h"
#include "Level.h"


struct TrackData
{
	string title;
	string artist;
	Time duration;

	TrackData() = default;

	TrackData(const string& _title, const string& _artist, const Time& _duration)
	{
		title = _title;
		artist = _artist;
		duration = _duration;
	}
};


class Track : public Actor
{
	string path;
	TrackData info;
	MusicSample* music;
	BeatMap* currentBeatMap;
	map<string, BeatMap> beatMaps;

public:
	FORCEINLINE TrackData GetInfo() const
	{
		return info;
	}

	
	FORCEINLINE string GetArtist() const
	{
		return info.artist;
	}
	FORCEINLINE string GetTitle() const
	{
		return info.title;
	}
	FORCEINLINE Time GetDuration() const
	{
		return info.duration;
	}

	FORCEINLINE string GetDurationAsString() const
	{
		const float _seconds = info.duration.asSeconds();
		const string _minutes = to_string(CAST(int, _seconds) / 60);
		const string _secondsString = to_string(CAST(int, _seconds) % 60);
		return _minutes + ":" + _secondsString;
	}
	FORCEINLINE MusicSample* GetMusic() const
	{
		return music;
	}
	FORCEINLINE map<string, BeatMap>& GetBeatMaps()
	{
		return beatMaps;
	}
	FORCEINLINE BeatMap* GetCurrentBeatMap()
	{
		return currentBeatMap;
	}


	FORCEINLINE bool IsFinished() const
	{
		return currentBeatMap->GetCurrentTime() > info.duration;
	}

public:
	Track(Level* _level, const string& _path = "default");
	Track(const Track& _other);
	~Track();

public:
	void PlayExtrait() const;

	void Start(const string& _difficulty);
	virtual void Tick(const float _deltaTime) override;
	void Stop();
private:
	void Init();

public:
	bool operator < (Track _other) const;
};

