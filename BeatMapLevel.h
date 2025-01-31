#pragma once
#include "Level.h"
#include "ScoreLabel.h"
#include "Track.h"
#include "NoteDetector.h"
#include "NoteSpawner.h"

class BeatMapLevel : public Game
{
	ScoreLabel* score;
	string name;
	string difficulty;
	Vector2u windowSize;
	map<NoteType, NoteDetector*> triggers;
	map<NoteType, NoteSpawner*> noteSpawners;

	Track* track;
	
	//float advancementPercent;

public:
	FORCEINLINE map<NoteType, NoteDetector*>& GetNoteDetectors()
	{
		return triggers;
	}
	FORCEINLINE NoteDetector* GetNoteDetector(const NoteType& _noteType)
	{
		return triggers[_noteType];
	}

	FORCEINLINE map<NoteType, NoteSpawner*>& GetNoteSpawners()
	{
		return noteSpawners;
	}
	FORCEINLINE NoteSpawner* GetNoteSpawner(const NoteType& _noteType)
	{
		return noteSpawners[_noteType];
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
	void InitNoteTriggerAndSpawner();

	void SpawnCombo(const u_int& _comboCout = 0, const Color& _color = Color(0, 0, 0));
};

