#pragma once
#include "Game.h"
#include "BeatMapLevel.h"
class RythmGame : public Game
{
	map<string, BeatMapLevel*> allLevels;

public:
	RythmGame();
	~RythmGame();
public:

	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;
};

