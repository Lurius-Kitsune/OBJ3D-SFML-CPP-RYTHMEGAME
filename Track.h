#pragma once
#include "CoreMinimal.h"
#include "BeatMap.h"
#include "MusicSample.h"
class Track
{
	string path;
	string artist;
	string title;
	Time duration;
	MusicSample* music;
	BeatMap* currentBeatMap;
	map<string, BeatMap> beatMaps;

public:
	FORCEINLINE string GetArtist() const
	{
		return artist;
	}
	FORCEINLINE string GetTitle() const
	{
		return title;
	}
	FORCEINLINE Time GetDuration() const
	{
		return duration;
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

public:
	Track(const string& _path = "default");
	~Track();

public:
	void Start(const string& _difficulty);
	void Update();
	void Stop();
private:
	void Init();

public:
	bool operator < (Track _other) const;
};

