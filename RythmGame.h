#pragma once
#include "Game.h"
#include "BeatMapLevel.h"
#include "MeshActor.h"
class RythmGame : public Game
{
	map<string, BeatMapLevel*> allLevels;
	MeshActor* background;

public:
	RythmGame();
	~RythmGame();
public:

	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;
};

