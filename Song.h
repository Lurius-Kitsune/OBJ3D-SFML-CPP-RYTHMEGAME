#pragma once
#include "CoreMinimal.h"
#include "BeatMap.h"
#include "MusicSample.h"
class Song
{
	string path;
	map<string, BeatMap> beatMaps;
	string artist;
	string title;
	Time duration;
	MusicSample* music;
	BeatMap* currentBeatMap;

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

public:
	Song(const string& _path);
	~Song();

public:
	void Start(const string& _difficulty);
private:
	void Init();
};

