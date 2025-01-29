#include "RythmGame.h"

RythmGame::RythmGame()
{
	allLevels = map<string, BeatMapLevel*>();
}

RythmGame::~RythmGame()
{
	for (const pair<string,BeatMapLevel*>& _beatLevel : allLevels)
	{
		delete _beatLevel.second;
	}
}

void RythmGame::Start()
{
	Super::Start();
	allLevels["Test"] = new BeatMapLevel("Song Name !", "Very Hard");
}

bool RythmGame::Update()
{
	Super::Update();

	allLevels["Test"]->Display();

	return IsOver();
}

void RythmGame::Stop()
{
	Super::Stop();


}
