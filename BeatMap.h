#pragma once
#include "CoreMinimal.h"

class BeatMap
{
	// map<float, Note> notes;
	int MissDamage;
	Time* timeStamp;

public:
	BeatMap(const int _missDamage, const float _timeStamp);
	BeatMap(const string& _path);
	~BeatMap();


public:
	void Start();
};

