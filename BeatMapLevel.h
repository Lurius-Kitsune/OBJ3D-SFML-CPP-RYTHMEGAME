#pragma once
#include "Level.h"
#include "HUD.h"
#include "ScoreLabel.h"
#include "Track.h"
#include "NoteDetector.h"
#include "NoteSpawner.h"


struct ComboData
{
	Label* label;
	u_int count;

	ComboData()
	{
		count = 0;
		label = M_HUD.CreateWidget<Label>("X " + to_string(count), Screen, "Test", TTF);
		label->SetVisibility(Hidden);
		M_HUD.AddToViewport(label);
	}

	ComboData& operator++()
	{
		SetCount(++count);
		return *this;
	}

	ComboData operator++(const int _value)
	{
		SetCount(count++);
		return *this;
	}

	ComboData& operator--()
	{
		SetCount(--count);
		return *this;
	}

	ComboData operator--(const int _value)
	{
		SetCount(count--);
		return *this;
	}

	FORCEINLINE void SetCount(const u_int& _count)
	{
		label->SetVisibility(_count == 0 ? Hidden : Visible);
		count = _count;
		label->GetText()->SetString("X " + to_string(count));
	}
};



class BeatMapLevel : public Game
{
	ScoreLabel* score;
	unique_ptr<ComboData> comboData;
	Vector2u windowSize;
	map<NoteType, NoteDetector*> triggers;
	map<NoteType, NoteSpawner*> noteSpawners;

	Track* track;
	TrackData* trackInfo;
	string difficulty;
	
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
	void IncrementCombo();

private:
	void InitLevelAspect(); //TODO change name Methode
	void InitHUD();
	void InitNoteTriggerAndSpawner();
};

