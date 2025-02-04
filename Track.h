#pragma once
#include "CoreMinimal.h"
#include "BeatMap.h"
#include "MusicSample.h"
#include "Image.h"

struct TrackData
{
	string title;
	string artist;
	Time duration;
	UI::Image* cover;
	TrackData() = default;

	TrackData(const string& _title, const string& _artist, const Time& _duration, UI::Image* _image)
	{
		title = _title;
		artist = _artist;
		duration = _duration;
		cover = _image;
	}

	~TrackData()
	{
		delete cover;
	}
};


class Track
{
	string path;
	unique_ptr<TrackData> info;
	MusicSample* music;
	BeatMap* currentBeatMap;
	map<string, BeatMap> beatMaps;

public:
	FORCEINLINE TrackData* GetInfo() const
	{
		return info.get();
	}

	
	FORCEINLINE string GetArtist() const
	{
		return info.get()->artist;
	}
	FORCEINLINE string GetTitle() const
	{
		return info.get()->title;
	}
	FORCEINLINE Time GetDuration() const
	{
		return info.get()->duration;
	}
	FORCEINLINE UI::Image* GetCover() const
	{
		return info.get()->cover;
	}

	FORCEINLINE string GetDurationAsString() const
	{
		const float _seconds = info.get()->duration.asSeconds();
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
		return currentBeatMap->GetCurrentTime() > info.get()->duration;
	}

public:
	Track(const string& _path = "default");
	~Track();

public:
	void PlayExtrait() const;

	void Start(const string& _difficulty);
	void Update();
	void Stop();
private:
	void Init();

public:
	bool operator < (Track _other) const;
};

