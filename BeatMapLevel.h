#pragma once
#include "Level.h"
#include "ScoreLabel.h"
class BeatMapLevel : public Game
{
	ScoreLabel* score;
	string name;
	string difficulty;
	Vector2u windowSize;
	//float advancementPercent;

public:
	BeatMapLevel(const string& _name, const string& _difficulty);

public:

	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;

private:
	void SpawnCombo(const u_int& _comboCout = 0, const Color& _color = Color(0, 0, 0));
};

