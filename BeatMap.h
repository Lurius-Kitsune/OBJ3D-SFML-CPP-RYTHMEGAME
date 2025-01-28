#pragma once
#include "CoreMinimal.h"
#include "Note.h"

class BeatMap
{
	string path;
	bool isLoaded;

	string difficulty;
	int missDamage;
	map<Time, NoteType> notes;
	Clock timeStamp;
	int perfectScoreMin;

	Actor* triggerNote;

public:
	Time GetCurrentTime()const
	{
		return timeStamp.getElapsedTime();
	}

	string GetCurrentTimeAsString()const
	{
		return to_string(timeStamp.getElapsedTime().asSeconds());
	}

public:
	BeatMap(const string& _path);
	~BeatMap();


public:
	void Start();

	void Update();


	void LoadBeatMap();
};

