#pragma once
#include "CoreMinimal.h"
#include "BeatMap.h"
#include "MusicSample.h"
class Tracks
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

public:
	Tracks(const string& _path = "default");
	~Tracks();

public:
	void Start(const string& _difficulty);
private:
	void Init();
	string InitInfo(const string& _infoLine);

public:
	bool operator < (Tracks _other) const;
};

