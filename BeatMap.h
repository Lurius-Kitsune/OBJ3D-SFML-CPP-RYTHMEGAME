#pragma once
#include "CoreMinimal.h"
#include "Note.h"

class BeatMap
{
	string path;
	bool isLoaded;
	map<float, Note> notes;
	int missDamage;
	Clock* timeStamp;
	string difficulty;

public:
	BeatMap(const string& _path);
	~BeatMap();


public:
	void Start();


	void LoadBeatMap();

	string GetCurrentTime()const
	{
		return to_string(timeStamp->getElapsedTime().asSeconds());
	}
};

