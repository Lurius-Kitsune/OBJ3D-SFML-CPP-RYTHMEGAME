#pragma once
#include "CoreMinimal.h"
#include "Note.h"

class BeatMap
{
	string path;
	bool isLoaded;

	string difficulty;
	int missDamage;
	map<Time, pair<NoteType, bool>> notes;
	Clock timeStamp;
	int perfectScoreMin;

public:
	Time GetCurrentTime()const
	{
		return timeStamp.getElapsedTime();
	}

	string GetCurrentTimeAsString()const
	{
		return to_string(timeStamp.getElapsedTime().asSeconds());
	}

	FORCEINLINE string GetDifficulty()
	{
		return difficulty;
	}

public:
	BeatMap() = default;
	BeatMap(const string& _path);
	~BeatMap();


public:
	void Start();

	void Update();

	void LoadBeatMap();
};

