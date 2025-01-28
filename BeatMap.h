#pragma once
#include "CoreMinimal.h"
#include "Note.h"

struct BeatMapPathList
{
	string path;
	vector<string> pathList;
	BeatMapPathList()
	{
		path = "Assets/BeatMap/";
		pathList =
		{
			path + "CrabRave.txt",
		};
	}
};

class BeatMap
{
	string path;
	bool isLoaded;
	map<Time, NoteType> notes;
	int missDamage;
	Clock timeStamp;
	string difficulty;

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
	BeatMap(const string& _path);
	~BeatMap();


public:
	void Start();

	void Update();


	void LoadBeatMap();
};

