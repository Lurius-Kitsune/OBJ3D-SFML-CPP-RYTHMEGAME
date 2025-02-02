#pragma once
#include "Level.h"
#include "ScoreLabel.h"
#include "Track.h"
#include "NoteDetector.h"

class BeatMapLevel : public Game
{
	ScoreLabel* score;
	string name;
	string difficulty;
	Vector2u windowSize;

	Track* track;
	map<NoteType, NoteDetector*> triggers;
	
	//float advancementPercent;

public:
	FORCEINLINE map<NoteType, NoteDetector*>& GetNoteDetector()
	{
		return triggers;
	}

public:
	BeatMapLevel(Track* _track, const string& _difficulty);

public:

	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;

private:
	void InitLevelAspect(); //TODO change name Methode
	void InitHUD();
	void InitNote(); //TODO change name Methode

	void SpawnCombo(const u_int& _comboCout = 0, const Color& _color = Color(0, 0, 0));
};

